#include "LogicSystem.h"


void LogicSystem::registerGet(const std::string& url, GetServicePtr func)
{
	m_getHandlerMap[url] = func;
}

void LogicSystem::registerPost(const std::string& url, PostServicePtr func)
{
	m_postHandlerMap[url] = func;
}

bool LogicSystem::handleGet(const std::string& url, std::shared_ptr<HttpConnection> conn)
{
	if (m_getHandlerMap.find(url) == m_getHandlerMap.end()) return false;

	m_getHandlerMap[url]->operator()(conn);
	return true;
}

bool LogicSystem::handlePost(const std::string& url, std::shared_ptr<HttpConnection> conn)
{
	if (m_postHandlerMap.find(url) == m_postHandlerMap.end()) return false;
	
	m_postHandlerMap[url]->operator()(conn);
	return true;
}

LogicSystem::LogicSystem()
{
	// �û���¼
	registerPost("/user_login", std::make_shared<LoginService>());
	// �û�ע��
	registerPost("/user_register", std::make_shared<RegisterService>());
	// �޸�����
	registerPost("/reset_pwd", std::make_shared<ResetService>());
	// ��ȡ��֤��
	registerPost("/get_varifycode", std::make_shared<GetVerifyCodeService>());
}