#pragma once

#include "const.h"
#include "Service.h"
#include "RedisDao.h"
#include "HttpConnection.h"

#include <map>
#include <memory>
#include <string>
#include <functional>

class HttpConnection;

class LogicSystem : public Singleton<LogicSystem>
{
public:

	using GetServicePtr = std::shared_ptr<GetService>;
	using PostServicePtr = std::shared_ptr<PostService>;

	~LogicSystem() = default;

	void registerGet(const std::string& url, GetServicePtr);
	void registerPost(const std::string& url, PostServicePtr);
	bool handleGet(const std::string& url, std::shared_ptr<HttpConnection> con);
	bool handlePost(const std::string& url, std::shared_ptr<HttpConnection> con);

private:

	// 单例模式
	LogicSystem();
	// 策略模式
	std::map<std::string, GetServicePtr> m_getHandlerMap;
	std::map<std::string, PostServicePtr> m_postHandlerMap;

};