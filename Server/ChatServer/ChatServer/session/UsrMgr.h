#pragma once

#include <map>

#include "Singleton.h"
#include "TcpConnection.h"

class TcpClient;

class UsrMgr : public Singleton<UsrMgr>
{
	friend class Singleton<UsrMgr>;

public:
	
	~UsrMgr();

	std::shared_ptr<TcpClient> getSession(int uid);
	void setUserSession(int uid, std::shared_ptr<TcpClient> session);
	void rmUserSession(int uid);

private:

	UsrMgr();

	std::mutex m_mutex;
	//uidµ½sessionµÄÓ³Éä
	std::map<int, std::shared_ptr<TcpClient>> m_sessions;

};