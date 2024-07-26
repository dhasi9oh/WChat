#include "RedisDao.h"

RedisDao::~RedisDao()
{
}

bool RedisDao::Get(const std::string& key, std::string& value)
{
	return false;
}

bool RedisDao::Set(const std::string& key, const std::string& value)
{
	return false;
}

bool RedisDao::LPush(const std::string& key, const std::string& value)
{
	return false;
}

bool RedisDao::LPop(const std::string& key, std::string& value)
{
	return false;
}

bool RedisDao::RPush(const std::string& key, const std::string& value)
{
	return false;
}

bool RedisDao::RPop(const std::string& key, std::string& value)
{
	return false;
}

bool RedisDao::HSet(const std::string& key, const std::string& hkey, const std::string& value)
{
	return false;
}

bool RedisDao::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	return false;
}

std::string RedisDao::HGet(const std::string& key, const std::string& hkey)
{
	return std::string();
}

bool RedisDao::Del(const std::string& key)
{
	return false;
}

bool RedisDao::ExistsKey(const std::string& key)
{
	return false;
}
