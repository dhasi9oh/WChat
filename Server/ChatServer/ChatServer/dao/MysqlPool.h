#pragma once

#include <queue>
#include <thread>
#include <memory>
#include <condition_variable>
#include <mysql_error.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

#include "const.h"


// 为每个连接维护一个last_oper_time，用于判断是否超时，超时则释放连接
class SqlConnection
{
public:

	SqlConnection(sql::Connection* connection, int last_oper_time)
		: m_connection(connection), m_last_oper_time(last_oper_time)
	{}

	std::unique_ptr<sql::Connection> m_connection;
	int m_last_oper_time;
};

// mysql的连接池
class MysqlPool
{
public:

	MysqlPool(int size
		, const std::string& url
		, const std::string& user
		, const std::string& password
		, const std::string& database);
	~MysqlPool();

	// 检查连接是否超时，超时则释放连接
	void checkConnection();
	// 归还mysql的连接
	void releaseConnection(std::unique_ptr<SqlConnection> connection);
	// 获取mysql的连接
	std::unique_ptr<SqlConnection> getConnection();
	// 关闭mysql连接池
	void close();

private:
	// mysql连接池的连接数量
	int m_size;
	// mysql的ip
	std::string m_url;
	// 用于登录mysql的用户
	std::string m_user;
	// 用于登录mysql的密码
	std::string m_password;
	// 要使用数据库的名称
	std::string m_database;
	// mysql连接池
	std::queue<std::unique_ptr<SqlConnection>> m_connections;
	// 定时检查连接的线程
	std::thread m_thread;
	// 线程退出标志
	bool b_stop;
	// 保证线程安全的互斥锁
	std::mutex m_mutex;
	// 唤醒线程的条件变量
	std::condition_variable m_cv;

};