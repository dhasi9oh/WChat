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

	// ��������Ƿ����
	bool checkEmail(const std::string& usr,const std::string& email);
	// ע���û�
	int registerUser(const std::string& username,const std::string& email, const std::string& password);
	// ��¼
	bool checkPassword(const std::string& email, const std::string& password, UserInfo& info);
	// ��������
	bool updatePassword(const std::string& username, const std::string& newPwd);

private:

	MysqlDao();

	std::unique_ptr<MysqlPool> m_pool;

};