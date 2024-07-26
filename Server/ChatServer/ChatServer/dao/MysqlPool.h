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


// Ϊÿ������ά��һ��last_oper_time�������ж��Ƿ�ʱ����ʱ���ͷ�����
class SqlConnection
{
public:

	SqlConnection(sql::Connection* connection, int last_oper_time)
		: m_connection(connection), m_last_oper_time(last_oper_time)
	{}

	std::unique_ptr<sql::Connection> m_connection;
	int m_last_oper_time;
};

// mysql�����ӳ�
class MysqlPool
{
public:

	MysqlPool(int size
		, const std::string& url
		, const std::string& user
		, const std::string& password
		, const std::string& database);
	~MysqlPool();

	// ��������Ƿ�ʱ����ʱ���ͷ�����
	void checkConnection();
	// �黹mysql������
	void releaseConnection(std::unique_ptr<SqlConnection> connection);
	// ��ȡmysql������
	std::unique_ptr<SqlConnection> getConnection();
	// �ر�mysql���ӳ�
	void close();

private:
	// mysql���ӳص���������
	int m_size;
	// mysql��ip
	std::string m_url;
	// ���ڵ�¼mysql���û�
	std::string m_user;
	// ���ڵ�¼mysql������
	std::string m_password;
	// Ҫʹ�����ݿ������
	std::string m_database;
	// mysql���ӳ�
	std::queue<std::unique_ptr<SqlConnection>> m_connections;
	// ��ʱ������ӵ��߳�
	std::thread m_thread;
	// �߳��˳���־
	bool b_stop;
	// ��֤�̰߳�ȫ�Ļ�����
	std::mutex m_mutex;
	// �����̵߳���������
	std::condition_variable m_cv;

};