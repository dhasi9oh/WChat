#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <memory>
#include <iostream>
#include <hiredis/hiredis.h>
#include <condition_variable>

#include "const.h"

// 为每个连接维护一个last_oper_time，用于判断是否超时，超时则释放连接
class RedisConnection
{
public:

	RedisConnection(redisContext* connection, int last_oper_time)
		: m_connection(connection), m_last_oper_time(last_oper_time)
	{}

	redisContext* m_connection;
	int m_last_oper_time;
};

class RedisPool
{
public:

	RedisPool(int size, const char* ip, int port, const char* password);

	~RedisPool();

	// 检查连接是否超时，超时则释放连接
	void checkConnection();
	// 归还redis的连接
	void releaseConnection(std::unique_ptr<RedisConnection> connection);
	// 获取redis的连接
	std::unique_ptr<RedisConnection> getConnection();
	// 关闭redis连接池
	void close();

private:

	// redis连接池的连接数量
	int m_size;
	// redis的ip
	std::string m_ip;
	// redis的端口
	int m_port;
	// 用于登录redis的密码
	std::string m_password;
	// redis连接池
	std::queue<std::unique_ptr<RedisConnection>> m_connections;
	// 定时检查连接的线程
	std::thread m_thread;
	// 线程退出标志
	bool b_stop;
	// 保证线程安全的互斥锁
	std::mutex m_mutex;
	// 唤醒线程的条件变量
	std::condition_variable m_cv;

};