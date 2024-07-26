#pragma once

#include "const.h"
#include "ConfigMgr.h"
#include "MysqlPool.h"
#include "Singleton.h"

struct UserInfo {
	std::string name;
	std::string pwd;
	int uid;
	std::string email;
};

class MysqlDao : public Singleton<MysqlDao>
{
	friend class Singleton<MysqlDao>;

public:

	// 检查邮箱是否存在
	bool checkEmail(const std::string& usr,const std::string& email);
	// 注册用户
	int registerUser(const std::string& username,const std::string& email, const std::string& password);
	// 登录
	bool checkPassword(const std::string& email, const std::string& password, UserInfo& info);
	// 更新密码
	bool updatePassword(const std::string& username, const std::string& newPwd);

private:

	MysqlDao();

	std::unique_ptr<MysqlPool> m_pool;

};