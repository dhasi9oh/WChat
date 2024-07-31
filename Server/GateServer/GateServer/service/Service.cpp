#include "Service.h"

void LoginService::operator()(ConnPtr conn_ptr)
{
	auto body_str = boost::beast::buffers_to_string(conn_ptr->getRequest().body().data());
	conn_ptr->getResponse().set(boost::beast::http::field::content_type, "text/json");

	//�������ɵ�json
	Json::Value src_root;
	//������ 
	Json::Reader reader;
	//���ص�json
	Json::Value root;
	
	//���л��ַ�����json������src_root
	if (!reader.parse(body_str, src_root)) {
		LOG_WARN("Failed to parse JSON data!");
		root["error"] = ErrorCodes::Error_Json;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	std::string email = src_root["email"].asString();
	std::string password = src_root["passwd"].asString();

	LOG_INFO("login user email is {}, password is {}", email, password);

	//��֤�û���Ϣ
	UserInfo info;
	bool success = MysqlDao::Instance()->checkPassword(email, password, info);

	if (!success) {
		LOG_WARN("user pwd not match");
		root["error"] = ErrorCodes::PasswdInvalid;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	//״̬���������صı���
	auto reply = StatusGrpcClient::Instance()->getChatServer(info.uid);

	if (reply.error()) {
		LOG_WARN(" grpc get chat server failed, error is {}", reply.error());
		root["error"] = ErrorCodes::RPCFailed;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	LOG_INFO("succeed to load userinfo uid is {}", info.uid);
	root["error"] = 0;
	root["email"] = email;
	root["uid"] = info.uid;
	root["token"] = reply.token();
	//�����������ip�Ͷ˿�
	root["host"] = reply.host();
	root["port"] = reply.port();

	boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
}

void RegisterService::operator()(ConnPtr conn_ptr)
{
	auto body_str = boost::beast::buffers_to_string(conn_ptr->getRequest().body().data());
	conn_ptr->getResponse().set(boost::beast::http::field::content_type, "text/json");

	//�������ɵ�json
	Json::Value src_root;
	//������ 
	Json::Reader reader;
	//���ص�json
	Json::Value root;

	//���л��ַ�����json������src_root
	if (!reader.parse(body_str, src_root)) {
		LOG_WARN("Failed to parse JSON data!");
		root["error"] = ErrorCodes::Error_Json;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	std::string email = src_root["email"].asString();
	std::string name = src_root["user"].asString();
	std::string pwd = src_root["passwd"].asString();
	std::string confirm = src_root["confirm"].asString();

	//������������벻һ��
	if (pwd != confirm) {
		LOG_WARN("password not match!");
		root["error"] = ErrorCodes::PasswdErr;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	//ע���û���Ҫ��֤��
	std::string varify_code;

	//��ȡ��֤��
	bool get_varify_code_success = RedisDao::Instance()->Get(CODEPREFIX + email, varify_code);

	//��֤�����
	if (!get_varify_code_success) {
		LOG_WARN("get varify code expired!");
		root["error"] = ErrorCodes::VarifyExpired;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	//��֤�����
	if (varify_code != src_root["varifycode"].asString()) {
		LOG_WARN("varify code not match!");
		root["error"] = ErrorCodes::VarifyCodeErr;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	//�������ݿ��ж��û��Ƿ����
	int uid = MysqlDao::Instance()->registerUser(name, email, pwd);

	//�û�����
	if (uid == 0 || uid == -1) {
		LOG_WARN("register user failed!");
		root["error"] = ErrorCodes::UserExist;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	root["error"] = 0;
	root["uid"] = uid;
	root["email"] = email;
	root["user"] = name;
	root["passwd"] = pwd;
	root["confirm"] = confirm;
	root["varifycode"] = varify_code;

	boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();

}

void ResetService::operator()(ConnPtr conn_ptr)
{
	auto body_str = boost::beast::buffers_to_string(conn_ptr->getRequest().body().data());
	conn_ptr->getResponse().set(boost::beast::http::field::content_type, "text/json");

	//�������ɵ�json
	Json::Value src_root;
	//������ 
	Json::Reader reader;
	//���ص�json
	Json::Value root;

	//���л��ַ�����json������src_root
	if (!reader.parse(body_str, src_root)) {
		LOG_WARN("Failed to parse JSON data!");
		root["error"] = ErrorCodes::Error_Json;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	std::string email = src_root["email"].asString();
	std::string pwd = src_root["passwd"].asString();
	std::string usr = src_root["user"].asString();

	//ע���û���Ҫ��֤��
	std::string varify_code;

	//��֤�����
	if (!RedisDao::Instance()->Get(CODEPREFIX + email, varify_code)) {
		LOG_WARN("get varify code expired!");
		root["error"] = ErrorCodes::VarifyExpired;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	//��֤�����
	if (varify_code != src_root["varifycode"].asString()) {
		LOG_WARN("varify code not match!");
		root["error"] = ErrorCodes::VarifyCodeErr;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	//�û������ڻ������䲻ƥ��
	if (!MysqlDao::Instance()->checkEmail(usr, email)) {
		LOG_WARN("user not exist or email not match!");
		root["error"] = ErrorCodes::EmailNotMatch;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	if (!MysqlDao::Instance()->updatePassword(usr, pwd)) {
		LOG_WARN("update password faield!");
		root["error"] = ErrorCodes::PasswdUpFailed;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	LOG_INFO("reset password succeed!");

	root["error"] = 0;
	root["email"] = email;
	root["user"] = usr;
	root["passwd"] = pwd;
	root["varifycode"] = varify_code;

	boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
}

void GetVerifyCodeService::operator()(ConnPtr conn_ptr)
{
	auto body_str = boost::beast::buffers_to_string(conn_ptr->getRequest().body().data());
	conn_ptr->getResponse().set(boost::beast::http::field::content_type, "text/json");

	//�������ɵ�json
	Json::Value src_root;
	//������ 
	Json::Reader reader;
	//���ص�json
	Json::Value root;

	//���л��ַ�����json������src_root
	if (!reader.parse(body_str, src_root)) {
		LOG_WARN("Failed to parse JSON data!");
		root["error"] = ErrorCodes::Error_Json;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	if (!src_root.isMember("email")) {
		LOG_WARN("Failed to parse JSON data!");
		root["error"] = ErrorCodes::Error_Json;
		boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
		return;
	}

	std::string email = src_root["email"].asString();
	auto reply = VericfyGrpcClientt::Instance()->GetVarifyCode(email);

	root["email"] = email;
	root["error"] = reply.error();

	boost::beast::ostream(conn_ptr->getResponse().body()) << root.toStyledString();
}
