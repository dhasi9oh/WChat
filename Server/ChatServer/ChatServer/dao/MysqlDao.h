#pragma once

#include "data.h"
#include "Loger.h"
#include "const.h"
#include "ConfigMgr.h"
#include "MysqlPool.h"
#include "Singleton.h"


class MysqlDao : public Singleton<MysqlDao>
{
	friend class Singleton<MysqlDao>;

public:

	// ��������Ƿ����
	bool checkEmail(const std::string& usr,const std::string& email);
	// ע���û�
	int registerUser(const std::string& username,const std::string& email, const std::string& password);
	// ��¼
	bool checkPassword(const std::string& email, const std::string& password, UsrInfo& info);
	// ��������
	bool updatePassword(const std::string& username, const std::string& newPwd);
	// ��Ӻ�������
	bool addFriendApply(int from_uid, int to_uid);
	// ����������֤
	bool authFriendApply(int from_uid, int to_uid);
	//��Ӻ���
	bool addFriend(int from_uid, int to_uid, const std::string& back_name);
	//��ȡ������Ϣͨ��uid
	std::shared_ptr<UsrInfo> getUserInfoByUid(int uid);
	//��ȡ������Ϣͨ���û���
	std::shared_ptr<UsrInfo> getUserInfoByName(const std::string& name);
	//��ȡ�����б�
	bool getApplyUsrList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list, int offset, int limit);
	bool getFriendList(int self_id, std::vector<std::shared_ptr<UsrInfo> >& user_info);

private:

	MysqlDao();

	std::unique_ptr<MysqlPool> m_pool;

};