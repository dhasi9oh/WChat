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

	auto server_list = cfg["ChatServers"]["name"];

	std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& word : words) {
		if (cfg[word]["name"].empty()) {
			continue;
		}

		ChatServer server;
		server.port = cfg[word]["port"];
		server.host = cfg[word]["host"];
		server.name = cfg[word]["name"];
		m_chatServers[server.name] = server;
	}
}

//�ͻ��˷���������Ҫ��¼
Status StatusServiceImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* response)
{
	auto uid = request->uid();
	auto token = request->token();

	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	std::string token_value = "";
	bool success = RedisDao::Instance()->Get(token_key, token_value);
	if (success) {
		response->set_error(ErrorCodes::UidInvalid);
		return Status::OK;
	}

	if (token_value != token) {
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

	LOG_INFO("host:{} port:{}", server.host, server.port);

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
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	RedisDao::Instance()->Set(token_key, token);
}

//ɾ��token
void StatusServiceImpl::removeToken(int uid)
{
}

//��ȡһ�������������ٵķ�����
ChatServer StatusServiceImpl::getChatServer()
{
	std::lock_guard<std::mutex> lock(m_serverMutex);
	auto minServer = m_chatServers.begin()->second;
	auto count_str = RedisDao::Instance()->HGet(LOGIN_COUNT, minServer.name);
	if (count_str.empty()) {
		//��������Ĭ������Ϊ���
		minServer.con_count = INT_MAX;
	}
	else {
		minServer.con_count = std::stoi(count_str);
	}


	// ʹ�÷�Χ����forѭ��
	for (auto& server : m_chatServers) {

		if (server.second.name == minServer.name) {
			continue;
		}

		auto count_str = RedisDao::Instance()->HGet(LOGIN_COUNT, server.second.name);
		if (count_str.empty()) {
			server.second.con_count = INT_MAX;
		}
		else {
			server.second.con_count = std::stoi(count_str);
		}

		if (server.second.con_count < minServer.con_count) {
			minServer = server.second;
		}
	}

	LOG_INFO("minServer:{}", minServer.name);

	return minServer;
}
