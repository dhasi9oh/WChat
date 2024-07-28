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

	// 检查邮箱是否存在
	bool checkEmail(const std::string& usr,const std::string& email);
	// 注册用户
	int registerUser(const std::string& username,const std::string& email, const std::string& password);
	// 登录
	bool checkPassword(const std::string& email, const std::string& password, UsrInfo& info);
	// 更新密码
	bool updatePassword(const std::string& username, const std::string& newPwd);
	// 添加好友申请
	bool addFriendApply(int from_uid, int to_uid);
	// 好友申请认证
	bool authFriendApply(int from_uid, int to_uid);
	//添加好友
	bool addFriend(int from_uid, int to_uid, const std::string& back_name);
	//获取个人信息通过uid
	std::shared_ptr<UsrInfo> getUserInfoByUid(int uid);
	//获取个人信息通过用户名
	std::shared_ptr<UsrInfo> getUserInfoByName(const std::string& name);
	//获取申请列表
	bool getApplyUsrList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list, int offset, int limit);
	bool getFriendList(int self_id, std::vector<std::shared_ptr<UsrInfo> >& user_info);

private:

	MysqlDao();

	std::unique_ptr<MysqlPool> m_pool;

};