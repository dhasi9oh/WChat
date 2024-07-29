#include "UsrMgr.h"

UsrMgr::~UsrMgr()
{
	m_sessions.clear();
}

std::shared_ptr<TcpClient> UsrMgr::getSession(int uid)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	auto iter = m_sessions.find(uid);
	if (iter == m_sessions.end()) {
		return nullptr;
	}

	return iter->second;
}

void UsrMgr::setUserSession(int uid, std::shared_ptr<TcpClient> session)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_sessions[uid] = session;
}

void UsrMgr::rmUserSession(int uid)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_sessions.erase(uid);
}

UsrMgr::UsrMgr()
{
}