#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <memory>
#include <iostream>
#include <hiredis/hiredis.h>
#include <condition_variable>

#include "const.h"

// Ϊÿ������ά��һ��last_oper_time�������ж��Ƿ�ʱ����ʱ���ͷ�����
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

	// ��������Ƿ�ʱ����ʱ���ͷ�����
	void checkConnection();
	// �黹redis������
	void releaseConnection(std::unique_ptr<RedisConnection> connection);
	// ��ȡredis������
	std::unique_ptr<RedisConnection> getConnection();
	// �ر�redis���ӳ�
	void close();

private:

	// redis���ӳص���������
	int m_size;
	// redis��ip
	std::string m_ip;
	// redis�Ķ˿�
	int m_port;
	// ���ڵ�¼redis������
	std::string m_password;
	// redis���ӳ�
	std::queue<std::unique_ptr<RedisConnection>> m_connections;
	// ��ʱ������ӵ��߳�
	std::thread m_thread;
	// �߳��˳���־
	bool b_stop;
	// ��֤�̰߳�ȫ�Ļ�����
	std::mutex m_mutex;
	// �����̵߳���������
	std::condition_variable m_cv;

};