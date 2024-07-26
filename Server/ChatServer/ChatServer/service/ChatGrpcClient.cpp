#include "ChatGrpcClient.h"


#include <jsoncpp/json/json.h>

ChatGrpcClient::ChatGrpcClient()
{
	auto& cfg = ConfigMgr::Instance();
	auto server_list = cfg["PeerServer"]["Servers"];

	std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& word : words) {
		if (cfg[word]["Name"].empty()) {
			continue;
		}
		_pools[cfg[word]["Name"]] = std::make_unique<ChatConPool>(5, cfg[word]["Host"], cfg[word]["Port"]);
	}

}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req)
{
	AddFriendRsp rsp;
	Defer defer([&rsp, &req]() {
		rsp.set_error(ErrorCodes::Success);
		rsp.set_applyuid(req.applyuid());
		rsp.set_touid(req.touid());
		});

	auto find_iter = _pools.find(server_ip);
	if (find_iter == _pools.end()) {
		return rsp;
	}

	auto& cfg = ConfigMgr::Instance();
	auto self_name = cfg["SelfServer"]["Name"];
	//ֱ��֪ͨ�Է���������Ϣ
	if (server_ip == self_name) {
		auto session = UsrMgr::Instance()->getSession(req.touid());
		if (session) {
			//���ڴ�����ֱ�ӷ���֪ͨ�Է�
			Json::Value  rtvalue;
			rtvalue["error"] = ErrorCodes::Success;
			rtvalue["applyuid"] = req.applyuid();
			rtvalue["name"] = req.name();
			rtvalue["desc"] = req.desc();
			std::string return_str = rtvalue.toStyledString();
			session->send(return_str, ID_NOTIFY_ADD_FRIEND_REQ);
		}

		return rsp;
	}

	auto& pool = find_iter->second;
	ClientContext context;
	auto stub = pool->getConnection();
	Status status = stub->NotifyAddFriend(&context, req, &rsp);
	Defer defercon([&stub, this, &pool]() {
		pool->returnConnection(std::move(stub));
		});

	if (!status.ok()) {
		rsp.set_error(ErrorCodes::RPCFailed);
		return rsp;
	}

	return rsp;
}


bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UsrInfo>& userinfo)
{
	//���Ȳ�redis�в�ѯ�û���Ϣ
	std::string info_str = "";
	bool b_base = RedisDao::Instance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		userinfo->uid = root["uid"].asInt();
		userinfo->name = root["name"].asString();
		userinfo->pwd = root["pwd"].asString();
		userinfo->email = root["email"].asString();
		userinfo->nick = root["nick"].asString();
		userinfo->desc = root["desc"].asString();
		userinfo->sex = root["sex"].asInt();
		userinfo->icon = root["icon"].asString();
	}
	else {
		//redis��û�����ѯmysql
		//��ѯ���ݿ�
		std::shared_ptr<UsrInfo> user_info = nullptr;
		user_info = MysqlDao::Instance()->getUserInfoByUid(uid);
		if (user_info == nullptr) {
			return false;
		}

		userinfo = user_info;

		//�����ݿ�����д��redis����
		Json::Value redis_root;
		redis_root["uid"] = uid;
		redis_root["pwd"] = userinfo->pwd;
		redis_root["name"] = userinfo->name;
		redis_root["email"] = userinfo->email;
		redis_root["nick"] = userinfo->nick;
		redis_root["desc"] = userinfo->desc;
		redis_root["sex"] = userinfo->sex;
		redis_root["icon"] = userinfo->icon;
		RedisDao::Instance()->Set(base_key, redis_root.toStyledString());
	}

}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req) {
	AuthFriendRsp rsp;
	Defer defer([&rsp, &req]() {
		rsp.set_error(ErrorCodes::Success);
		rsp.set_fromuid(req.fromuid());
		rsp.set_touid(req.touid());
		});

	auto find_iter = _pools.find(server_ip);
	if (find_iter == _pools.end()) {
		return rsp;
	}

	auto& cfg = ConfigMgr::Instance();
	auto self_name = cfg["SelfServer"]["Name"];
	//ֱ��֪ͨ�Է�����֤ͨ����Ϣ
	if (server_ip == self_name) {
		auto session = UsrMgr::Instance()->getSession(req.touid());
		if (session) {
			//���ڴ�����ֱ�ӷ���֪ͨ�Է�
			Json::Value  rtvalue;
			rtvalue["error"] = ErrorCodes::Success;
			rtvalue["fromuid"] = req.fromuid();
			rtvalue["touid"] = req.touid();
			std::string base_key = USER_BASE_INFO + std::to_string(req.touid());
			auto user_info = std::make_shared<UsrInfo>();
			bool b_info = GetBaseInfo(base_key, req.touid(), user_info);
			if (b_info) {
				rtvalue["name"] = user_info->name;
				rtvalue["nick"] = user_info->nick;
				rtvalue["icon"] = user_info->icon;
				rtvalue["sex"] = user_info->sex;
			}
			else {
				rtvalue["error"] = ErrorCodes::UidInvalid;
			}


			std::string return_str = rtvalue.toStyledString();
			session->send(return_str, ID_NOTIFY_AUTH_FRIEND_REQ);
		}

		return rsp;
	}

	auto& pool = find_iter->second;
	ClientContext context;
	auto stub = pool->getConnection();
	Status status = stub->NotifyAuthFriend(&context, req, &rsp);
	Defer defercon([&stub, this, &pool]() {
		pool->returnConnection(std::move(stub));
		});

	if (!status.ok()) {
		rsp.set_error(ErrorCodes::RPCFailed);
		return rsp;
	}

	return rsp;
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue)
{
	TextChatMsgRsp rsp;
	rsp.set_error(ErrorCodes::Success);

	Defer defer([&rsp, &req]() {
		rsp.set_fromuid(req.fromuid());
		rsp.set_touid(req.touid());
		for (const auto& text_data : req.textmsgs()) {
			TextChatData* new_msg = rsp.add_textmsgs();
			new_msg->set_msgid(text_data.msgid());
			new_msg->set_msgcontent(text_data.msgcontent());
		}

		});

	auto find_iter = _pools.find(server_ip);
	if (find_iter == _pools.end()) {
		return rsp;
	}

	auto& cfg = ConfigMgr::Instance();
	auto self_name = cfg["SelfServer"]["Name"];
	//ֱ��֪ͨ�Է�����֤ͨ����Ϣ
	if (server_ip == self_name) {
		auto session = UsrMgr::Instance()->getSession(req.touid());
		if (session) {
			//���ڴ�����ֱ�ӷ���֪ͨ�Է�
			std::string return_str = rtvalue.toStyledString();
			session->send(return_str, ID_NOTIFY_TEXT_CHAT_MSG_REQ);
		}

		return rsp;
	}

	auto& pool = find_iter->second;
	ClientContext context;
	auto stub = pool->getConnection();
	Status status = stub->NotifyTextChatMsg(&context, req, &rsp);
	Defer defercon([&stub, this, &pool]() {
		pool->returnConnection(std::move(stub));
		});

	if (!status.ok()) {
		rsp.set_error(ErrorCodes::RPCFailed);
		return rsp;
	}

	return rsp;
}

