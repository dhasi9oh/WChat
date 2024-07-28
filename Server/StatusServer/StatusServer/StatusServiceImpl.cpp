#include "StatusServiceImpl.h"

std::string generate_unique_string() {
	// ����UUID����
	boost::uuids::uuid uuid = boost::uuids::random_generator()();

	// ��UUIDת��Ϊ�ַ���
	std::string unique_string = boost::uuids::to_string(uuid);

	return unique_string;
}

//ע����������������Ϣ
StatusServiceImpl::StatusServiceImpl()
{
	auto& cfg = ConfigMgr::Instance();
	ChatServer server;
	server.port = cfg["ChatServer1"]["port"];
	server.host = cfg["ChatServer1"]["host"];
	server.con_count = 0;
	server.name = cfg["ChatServer1"]["name"];
	m_chatServers[server.name] = server;

	server.port = cfg["ChatServer2"]["port"];
	server.host = cfg["ChatServer2"]["host"];
	server.name = cfg["ChatServer2"]["name"];
	server.con_count = 0;
	m_chatServers[server.name] = server;
}

//�ͻ��˷���������Ҫ��¼
Status StatusServiceImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* response)
{
	auto uid = request->uid();
	auto token = request->token();

	std::lock_guard<std::mutex> lock(m_tokenMutex);
	auto iter = m_tokens.find(uid);

	if (m_tokens.end() == iter) {
		response->set_error(ErrorCodes::UidInvalid);
		return Status::OK;
	}

	if (iter->second != token) {
		response->set_error(ErrorCodes::TokenInvalid);
		return Status::OK;
	}

	response->set_error(ErrorCodes::Success);
	response->set_uid(uid);
	response->set_token(token);

	return Status::OK;
}

//�ͻ��˷���������Ҫһ�������������ַ
Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* response)
{
	const auto& server = getChatServer();

	response->set_host(server.host);
	response->set_port(server.port);
	response->set_error(ErrorCodes::Success);
	response->set_token(generate_unique_string());
	insertToken(request->uid(), response->token());

	return Status::OK;
}

//����token
void StatusServiceImpl::insertToken(int uid, std::string token)
{
	std::lock_guard<std::mutex> lock(m_tokenMutex);
	m_tokens[uid] = token;
}

//ɾ��token
void StatusServiceImpl::removeToken(int uid)
{
	std::lock_guard<std::mutex> lock(m_tokenMutex);
	m_tokens.erase(uid);
}

//��ȡһ�������������ٵķ�����
ChatServer StatusServiceImpl::getChatServer()
{
	std::lock_guard<std::mutex> lock(m_serverMutex);
	ChatServer server = m_chatServers.begin()->second;

	for (const auto& chat_server : m_chatServers) {
		if (chat_server.second.con_count < server.con_count) {
			server = chat_server.second;
		}
	}

	return server;
}
