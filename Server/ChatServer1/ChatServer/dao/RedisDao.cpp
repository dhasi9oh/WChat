#include "RedisDao.h"

RedisDao::~RedisDao()
{
}

RedisDao::RedisDao()
{
	auto& cfg_mgr = ConfigMgr::Instance();
	auto host = cfg_mgr["Redis"]["host"];
	auto port = cfg_mgr["Redis"]["port"];
	auto password = cfg_mgr["Redis"]["password"];
}

bool RedisDao::Get(const std::string& key, std::string& value)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}

	auto reply = (redisReply*)redisCommand(connect->m_connection, "GET %s", key.c_str());
	if (reply == nullptr) {
		LOG_WARN("[ GET  {} ] failed", key);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	if (reply->type != REDIS_REPLY_STRING) {
		LOG_WARN("[ GET  {} ] failed", key);
		freeReplyObject(reply);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	value = reply->str;
	freeReplyObject(reply);

	LOG_INFO("Succeed to execute command [ GET  {} ] failed", key);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::Set(const std::string& key, const std::string& value) {
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "SET %s %s", key.c_str(), value.c_str());

	if (nullptr == reply)
	{
		LOG_WARN("Execut command [ SET {}  {} ] failed !", key, value);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	if (!(reply->type == REDIS_REPLY_STATUS && (strcmp(reply->str, "OK") == 0 || strcmp(reply->str, "ok") == 0)))
	{
		LOG_WARN("Execut command [ SET {}  {} ] failed !", key, value);
		freeReplyObject(reply);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	freeReplyObject(reply);
	LOG_INFO("Execut command [ SET {}  {} ] success !", key, value);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::LPush(const std::string& key, const std::string& value)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "LPUSH %s %s", key.c_str(), value.c_str());
	if (nullptr == reply)
	{
		LOG_WARN("Execut command [ LPUSH {}  {} ] failure !", key, value);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		LOG_WARN("Execut command [ LPUSH {}  {} ] failure !", key, value);
		freeReplyObject(reply);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	LOG_INFO("Execut command [ LPUSH {}  {} ] success !", key, value);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::LPop(const std::string& key, std::string& value) {
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "LPOP %s ", key.c_str());
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		LOG_WARN("Execut command [ LPOP {} ] failure !", key);
		if (reply != nullptr) {
			freeReplyObject(reply);
		}
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}
	value = reply->str;
	LOG_INFO("Execut command [ LPOP {} ] success !", key);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::RPush(const std::string& key, const std::string& value) {
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "RPUSH %s %s", key.c_str(), value.c_str());
	if (nullptr == reply)
	{
		LOG_WARN("Execut command [ RPUSH {}  {} ] failure !", key, value);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {

		LOG_WARN("Execut command [ RPUSH {}  {} ] failure !", key, value);
		freeReplyObject(reply);
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	LOG_INFO("Execut command [ RPUSH {}  {} ] success !", key, value);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}
bool RedisDao::RPop(const std::string& key, std::string& value) {
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "RPOP %s ", key.c_str());
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {

		LOG_WARN("Execut command [ RPOP {} ] failure !", key);
		if (reply != nullptr) {
			freeReplyObject(reply);
		}
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}
	value = reply->str;
	LOG_INFO("Execut command [ RPOP {} ] success !", key);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::HSet(const std::string& key, const std::string& hkey, const std::string& value) {
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		LOG_WARN("Execut command [ HSet {}  {}  {} ] failure ! ", key, hkey, value);
		if (reply != nullptr) {
			freeReplyObject(reply);
		}
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}
	LOG_INFO("Execut command [ HSet {}  {}  {} ] success ! ", key, hkey, value);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;

	auto reply = (redisReply*)redisCommandArgv(connect->m_connection, 4, argv, argvlen);
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		LOG_WARN("Execut command [ HSet {}  {}  {} ] failure ! ", key, hkey, hvalue);
		if (reply != nullptr) {
			freeReplyObject(reply);
		}
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}
	LOG_INFO("Execut command [ HSet {}  {}  {} ] success ! ", key, hkey, hvalue);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

std::string RedisDao::HGet(const std::string& key, const std::string& hkey)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return "";
	}
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();

	auto reply = (redisReply*)redisCommandArgv(connect->m_connection, 3, argv, argvlen);
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		if (reply != nullptr) {
			freeReplyObject(reply);
		}

		LOG_WARN("Execut command [ HGet {}  {} ] failure ! ", key, hkey);
		m_redisPool->releaseConnection(std::move(connect));
		return "";
	}

	std::string value = reply->str;
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	LOG_INFO("Execut command [ HGet {}  {} ] success ! ", key, hkey);
	return value;
}

bool RedisDao::HDel(const std::string& key, const std::string& field)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}

	Defer defer([&connect, this]() {
		m_redisPool->releaseConnection(std::move(connect));
		});

	redisReply* reply = (redisReply*)redisCommand(connect->m_connection, "HDEL %s %s", key.c_str(), field.c_str());
	if (reply == nullptr) {
		std::cerr << "HDEL command failed" << std::endl;
		return false;
	}

	bool success = false;
	if (reply->type == REDIS_REPLY_INTEGER) {
		success = reply->integer > 0;
	}

	freeReplyObject(reply);
	return success;
}

bool RedisDao::Del(const std::string& key)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect->m_connection, "DEL %s", key.c_str());
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {

		LOG_WARN("Execut command [ Del {}  ] failure ! ", key);
		if (reply != nullptr) {
			freeReplyObject(reply);
		}
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}
	LOG_INFO("Execut command [ Del {} ] success ! ", key);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}

bool RedisDao::ExistsKey(const std::string& key)
{
	auto connect = m_redisPool->getConnection();
	if (connect == nullptr) {
		return false;
	}

	auto reply = (redisReply*)redisCommand(connect->m_connection, "exists %s", key.c_str());
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER || reply->integer == 0) {
		LOG_WARN("Not Found [ Key {} ] !", key);
		if (reply != nullptr) {
			freeReplyObject(reply);
		}
		m_redisPool->releaseConnection(std::move(connect));
		return false;
	}

	LOG_INFO(" Found [ Key {} ] exists !", key);
	freeReplyObject(reply);
	m_redisPool->releaseConnection(std::move(connect));
	return true;
}