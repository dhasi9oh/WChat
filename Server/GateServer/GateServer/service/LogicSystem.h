#pragma once

#include "const.h"
#include "Service.h"
#include "RedisDao.h"
#include "HttpConnection.h"

#include <map>
#include <string>
#include <functional>

class LogicSystem : public Singleton<LogicSystem>
{
public:
	
	using PostServicePtr = std::shared_ptr<PostService>;
	using GetServicePtr = std::shared_ptr<GetService>;

	~LogicSystem() = default;

	void registerGet(const std::string& url, GetServicePtr);
	void registerPost(const std::string& url, PostServicePtr);
	bool handleGet(const std::string& url, std::shared_ptr<HttpConnection> conn);
	bool handlePost(const std::string& url, std::shared_ptr<HttpConnection> conn);

private:

	// ����ģʽ
	LogicSystem();
	// ����ģʽ
	std::map<std::string, GetServicePtr> m_getHandlerMap;
	std::map<std::string, PostServicePtr> m_postHandlerMap;

};