#include "LogicSystem.h"

LogicSystem::~LogicSystem()
{
	b_stop = true;
	m_cv.notify_all();
	m_thread.join();
}

void LogicSystem::postMsgToQue(std::shared_ptr<LogicNode> node)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	//在队列大小未超过上限时和停止时获取锁
	m_cv.wait(lock, [this] { return m_msgQue.size() < MAX_SEND_QUEUE_SIZE || b_stop; });

	if (b_stop) {
		return;
	}

	m_msgQue.push(node);
}

LogicSystem::LogicSystem()
	: b_stop(false)
{
	registerCallBacks();
	m_thread = std::thread(&LogicSystem::dealMsg, this);
}

void LogicSystem::dealMsg()
{
	while (true) {
		std::vector<std::function<void()>> vf;
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			//判断队列是否为空或者是否停止
			m_cv.wait(lock, [this] { return !m_msgQue.empty() || b_stop; });
			//获取队列中所有节点并清空队列继续执行
			std::queue<std::shared_ptr<LogicNode>> msg_que;
			msg_que.swap(m_msgQue);

			while (!msg_que.empty()) {
				//获取队列中的头节点
				auto node_ptr = msg_que.front();
				msg_que.pop();
				//根据消息ID查找对应的回调函数并添加到vf中
				auto func_iter = m_callBackMap.find(node_ptr->m_recvNode->m_msg_id);
				if (func_iter != m_callBackMap.end()) {
					vf.push_back(
						std::bind(
							func_iter->second,
							node_ptr->m_session,
							node_ptr->m_recvNode->m_msg_id,
							node_ptr->m_recvNode->data_ptr)
					);
				}
			}
			//判断是否停止
			if (b_stop) {
				for (auto& func : vf) {
					func();
				}
				break;
			}
		}
		for (auto& func : vf) {
			func();
		}
	}
}

void LogicSystem::registerCallBacks()
{
	m_callBackMap[MSG_CHAT_LOGIN] = 
		std::bind(&LogicSystem::loginHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	m_callBackMap[ID_SEARCH_USER_REQ] =
		std::bind(&LogicSystem::searchInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	m_callBackMap[ID_ADD_FRIEND_REQ] =
		std::bind(&LogicSystem::loginHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	m_callBackMap[ID_AUTH_FRIEND_REQ] =
		std::bind(&LogicSystem::searchInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void LogicSystem::loginHandler(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(message, root);
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();

	Json::Value  info;
	Defer defer([this, &info, session]() {
		std::string return_str = info.toStyledString();
		session->send(return_str, MSG_CHAT_LOGIN_RSP);
		});

	//从redis获取用户token是否正确
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	std::string token_value = "";
	bool success = RedisDao::Instance()->Get(token_key, token_value);
	if (!success) {
		info["error"] = ErrorCodes::UidInvalid;
		return;
	}

	if (token_value != token) {
		info["error"] = ErrorCodes::TokenInvalid;
		return;
	}

	info["error"] = ErrorCodes::Success;

	std::string base_key = USER_BASE_INFO + uid_str;
	auto user_info = std::make_shared<UsrInfo>();
	bool b_base = getUserBaseInfo(base_key, uid, user_info);
	if (!b_base) {
		info["error"] = ErrorCodes::UidInvalid;
		return;
	}
	info["uid"] = uid;
	info["pwd"] = user_info->pwd;
	info["name"] = user_info->name;
	info["email"] = user_info->email;
	info["nick"] = user_info->nick;
	info["desc"] = user_info->desc;
	info["sex"] = user_info->sex;
	info["icon"] = user_info->icon;

	//从数据库获取申请列表
	std::vector<std::shared_ptr<ApplyInfo>> apply_list;
	auto b_apply = getFriendApplyListInfo(uid, apply_list);
	if (b_apply) {
		for (auto& apply : apply_list) {
			Json::Value obj;
			obj["name"] = apply->name;
			obj["uid"] = apply->uid;
			obj["icon"] = apply->icon;
			obj["nick"] = apply->nick;
			obj["sex"] = apply->sex;
			obj["desc"] = apply->desc;
			obj["status"] = apply->status;
			info["apply_list"].append(obj);
		}
	}

	//获取好友列表
	std::vector<std::shared_ptr<UsrInfo>> friend_list;
	bool b_friend_list = getFriendListInfo(uid, friend_list);
	for (auto& friend_ele : friend_list) {
		Json::Value obj;
		obj["name"] = friend_ele->name;
		obj["uid"] = friend_ele->uid;
		obj["icon"] = friend_ele->icon;
		obj["nick"] = friend_ele->nick;
		obj["sex"] = friend_ele->sex;
		obj["desc"] = friend_ele->desc;
		obj["back"] = friend_ele->back;
		info["friend_list"].append(obj);
	}

	auto server_name = ConfigMgr::Instance().getConfigItem("SelfServer", "Name");
	//将登录数量增加
	auto rd_res = RedisDao::Instance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisDao::Instance()->HSet(LOGIN_COUNT, server_name, count_str);
	//session绑定用户uid
	session->setUserID(uid);
	//为用户设置登录ip server的名字
	std::string  ipkey = USERIPPREFIX + uid_str;
	RedisDao::Instance()->Set(ipkey, server_name);
	//uid和session绑定管理,方便以后踢人操作
	UsrMgr::Instance()->setUserSession(uid, session);
}

void LogicSystem::searchInfo(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(message, root);
	auto uid_str = root["uid"].asString();

	Json::Value  info;

	Defer defer([this, &info, session]() {
		std::string return_str = info.toStyledString();
		session->send(return_str, ID_SEARCH_USER_RSP);
		});

	bool b_digit = isPureDigit(uid_str);
	if (b_digit) {
		getUserInfoByUid(uid_str, info);
	}
	else {
		getUserInfoByName(uid_str, info);
	}
}

void LogicSystem::addFriendApply(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(message, root);
	auto uid = root["uid"].asInt();
	auto applyname = root["applyname"].asString();
	auto bakname = root["bakname"].asString();
	auto touid = root["touid"].asInt();

	Json::Value  info;
	info["error"] = ErrorCodes::Success;
	Defer defer([this, &info, session]() {
		std::string return_str = info.toStyledString();
		session->send(return_str, ID_ADD_FRIEND_RSP);
		});

	//先更新数据库
	MysqlDao::Instance()->addFriendApply(uid, touid);

	//查询redis 查找touid对应的server ip
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisDao::Instance()->Get(to_ip_key, to_ip_value);
	if (!b_ip) {
		return;
	}

	AddFriendReq add_req;
	add_req.set_applyuid(uid);
	add_req.set_touid(touid);
	add_req.set_name(applyname);
	add_req.set_desc("");

	//发送通知
	ChatGrpcClient::Instance()->NotifyAddFriend(to_ip_value, add_req);
}

void LogicSystem::authFriendApply(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(message, root);

	auto uid = root["fromuid"].asInt();
	auto touid = root["touid"].asInt();
	auto back_name = root["back"].asString();
	std::cout << "from " << uid << " auth friend to " << touid << std::endl;

	Json::Value  info;
	info["error"] = ErrorCodes::Success;
	auto user_info = std::make_shared<UsrInfo>();

	std::string base_key = USER_BASE_INFO + std::to_string(touid);
	bool b_info = getUserBaseInfo(base_key, touid, user_info);
	if (b_info) {
		info["name"] = user_info->name;
		info["nick"] = user_info->nick;
		info["icon"] = user_info->icon;
		info["sex"] = user_info->sex;
		info["uid"] = user_info->uid;
	}
	else {
		info["error"] = ErrorCodes::UidInvalid;
	}


	Defer defer([this, &info, session]() {
		std::string return_str = info.toStyledString();
		session->send(return_str, ID_AUTH_FRIEND_RSP);
		});

	//先更新数据库
	MysqlDao::Instance()->authFriendApply(uid, touid);

	//更新数据库添加好友
	MysqlDao::Instance()->addFriend(uid, touid, back_name);

	//查询redis 查找touid对应的server ip
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisDao::Instance()->Get(to_ip_key, to_ip_value);
	if (!b_ip) {
		return;
	}

	AuthFriendReq auth_req;
	auth_req.set_fromuid(uid);
	auth_req.set_touid(touid);

	//发送通知
	ChatGrpcClient::Instance()->NotifyAuthFriend(to_ip_value, auth_req);
}

void LogicSystem::dealChatTextMsg(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(message, root);

	auto uid = root["fromuid"].asInt();
	auto touid = root["touid"].asInt();

	const Json::Value  arrays = root["text_array"];
	for (const auto& txt_obj : arrays) {
		auto content = txt_obj["content"].asString();
		auto msgid = txt_obj["msgid"].asString();
	}

	Json::Value  rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	rtvalue["text_array"] = arrays;
	rtvalue["fromuid"] = uid;
	rtvalue["touid"] = touid;

	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->send(return_str, ID_TEXT_CHAT_MSG_RSP);
		});


	//查询redis 查找touid对应的server ip
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisDao::Instance()->Get(to_ip_key, to_ip_value);
	if (!b_ip) {
		return;
	}

	TextChatMsgReq text_msg_req;
	text_msg_req.set_fromuid(uid);
	text_msg_req.set_touid(touid);


	//发送通知 todo...
	ChatGrpcClient::Instance()->NotifyTextChatMsg(to_ip_value, text_msg_req, rtvalue);
}

bool LogicSystem::isPureDigit(const std::string& uid)
{
	for (char c : uid) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

void LogicSystem::getUserInfoByUid(const std::string& uid_str, Json::Value& info)
{
	info["error"] = ErrorCodes::Success;

	std::string base_key = USER_BASE_INFO + uid_str;

	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisDao::Instance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		auto nick = root["nick"].asString();
		auto desc = root["desc"].asString();
		auto sex = root["sex"].asInt();

		info["uid"] = uid;
		info["pwd"] = pwd;
		info["name"] = name;
		info["email"] = email;
		info["nick"] = nick;
		info["desc"] = desc;
		info["sex"] = sex;
		return;
	}

	int uid = std::stoi(uid_str);
	//redis中没有则查询mysql
	//查询数据库
	std::shared_ptr<UsrInfo> user_info = nullptr;
	user_info = MysqlDao::Instance()->getUserInfoByUid(uid);
	if (user_info == nullptr) {
		info["error"] = ErrorCodes::UidInvalid;
		return;
	}

	//将数据库内容写入redis缓存
	Json::Value redis_root;
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->pwd;
	redis_root["name"] = user_info->name;
	redis_root["email"] = user_info->email;
	redis_root["nick"] = user_info->nick;
	redis_root["desc"] = user_info->desc;
	redis_root["sex"] = user_info->sex;

	RedisDao::Instance()->Set(base_key, redis_root.toStyledString());
	auto server_name = ConfigMgr::Instance().getConfigItem("SelfServer", "Name");
	//将登录数量增加
	auto rd_res = RedisDao::Instance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisDao::Instance()->HSet(LOGIN_COUNT, server_name, count_str);

	//返回数据
	info["uid"] = user_info->uid;
	info["pwd"] = user_info->pwd;
	info["name"] = user_info->name;
	info["email"] = user_info->email;
	info["nick"] = user_info->nick;
	info["desc"] = user_info->desc;
	info["sex"] = user_info->sex;
}

void LogicSystem::getUserInfoByName(const std::string& name, Json::Value& info)
{
	info["error"] = ErrorCodes::Success;

	std::string base_key = NAME_INFO + name;

	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisDao::Instance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		auto nick = root["nick"].asString();
		auto desc = root["desc"].asString();
		auto sex = root["sex"].asInt();

		info["uid"] = uid;
		info["pwd"] = pwd;
		info["name"] = name;
		info["email"] = email;
		info["nick"] = nick;
		info["desc"] = desc;
		info["sex"] = sex;
		return;
	}

	//redis中没有则查询mysql
	//查询数据库
	std::shared_ptr<UsrInfo> user_info = nullptr;
	user_info = MysqlDao::Instance()->getUserInfoByName(name);
	if (user_info == nullptr) {
		info["error"] = ErrorCodes::UidInvalid;
		return;
	}

	//将数据库内容写入redis缓存
	Json::Value redis_root;
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->pwd;
	redis_root["name"] = user_info->name;
	redis_root["email"] = user_info->email;
	redis_root["nick"] = user_info->nick;
	redis_root["desc"] = user_info->desc;
	redis_root["sex"] = user_info->sex;

	RedisDao::Instance()->Set(base_key, redis_root.toStyledString());
	auto server_name = ConfigMgr::Instance().getConfigItem("SelfServer", "Name");
	//将登录数量增加
	auto rd_res = RedisDao::Instance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisDao::Instance()->HSet(LOGIN_COUNT, server_name, count_str);

	//返回数据
	info["uid"] = user_info->uid;
	info["pwd"] = user_info->pwd;
	info["name"] = user_info->name;
	info["email"] = user_info->email;
	info["nick"] = user_info->nick;
	info["desc"] = user_info->desc;
	info["sex"] = user_info->sex;
}

bool LogicSystem::getUserBaseInfo(const std::string& base_key, int uid, std::shared_ptr<UsrInfo>& info)
{
	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisDao::Instance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		info->uid = root["uid"].asInt();
		info->name = root["name"].asString();
		info->pwd = root["pwd"].asString();
		info->email = root["email"].asString();
		info->nick = root["nick"].asString();
		info->desc = root["desc"].asString();
		info->sex = root["sex"].asInt();
		info->icon = root["icon"].asString();
	}
	else {
		//redis中没有则查询mysql
		//查询数据库
		std::shared_ptr<UsrInfo> user_info = nullptr;
		user_info = MysqlDao::Instance()->getUserInfoByUid(uid);
		if (user_info == nullptr) {
			return false;
		}

		info = user_info;

		//将数据库内容写入redis缓存
		Json::Value redis_root;
		redis_root["uid"] = uid;
		redis_root["pwd"] = info->pwd;
		redis_root["name"] = info->name;
		redis_root["email"] = info->email;
		redis_root["nick"] = info->nick;
		redis_root["desc"] = info->desc;
		redis_root["sex"] = info->sex;
		redis_root["icon"] = info->icon;
		RedisDao::Instance()->Set(base_key, redis_root.toStyledString());
	}

}

bool LogicSystem::getFriendApplyListInfo(int uid, std::vector<std::shared_ptr<ApplyInfo>>& info_list)
{
	//从mysql获取好友申请列表
	return MysqlDao::Instance()->getApplyUsrList(uid, info_list, 0, 10);
}

bool LogicSystem::getFriendListInfo(int uid, std::vector<std::shared_ptr<UsrInfo>>& info_list)
{
	return MysqlDao::Instance()->getFriendList(uid, info_list);
}
