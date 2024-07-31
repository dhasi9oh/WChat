#include "RedisPool.h"

RedisPool::RedisPool(int size, const char* ip, int port, const char* password)
	: m_size(size)
	, m_ip(ip)
	, m_port(port)
	, m_password(password)
	, b_stop(false)
{
	try {
		for (int i = 0; i < size; i++) {
			//申请一个redis连接
			auto* conn = redisConnect(m_ip.c_str(), m_port);
			//如果连接失败，则释放连接
			if (conn == nullptr || conn->err) {
				if (conn) {
					LOG_WARN("RedisPool::checkConnection reconnect failed: {}", conn->errstr);
					redisFree(conn);
				}
				continue;
			}
			//如果设置密码，则进行验证
			auto reply = reinterpret_cast<redisReply*>(redisCommand(conn, "AUTH %s", password));
			//验证失败
			if (reply->type == REDIS_REPLY_ERROR) {
				LOG_WARN("RedisPool::RedisPool auth failed: {}", reply->str);
				freeReplyObject(reply);
				continue;
			}

			//验证成功
			LOG_INFO("RedisPool::RedisPool auth success");
			freeReplyObject(reply);

			//获取当前时间戳
			auto cur_time = std::chrono::system_clock::now().time_since_epoch();
			long long time = std::chrono::duration_cast<std::chrono::seconds>(cur_time).count();

			m_connections.push(std::make_unique<RedisConnection>(conn, time));
		}

		//启动定时检查连接线程
		m_thread = std::thread(
			[this] {
				while (!b_stop) {
					checkConnection();
					std::this_thread::sleep_for(std::chrono::seconds(60));
				}
			}
		);

		m_thread.detach();
	}
	catch (const std::exception& e) {
		LOG_ERR("RedisPool::RedisPool init failed: {}", e.what());
	}
}

RedisPool::~RedisPool()
{
	close();
}

void RedisPool::checkConnection()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	int pool_size = m_connections.size();
	//获取当前时间
	auto cur_time = std::chrono::system_clock::now().time_since_epoch();
	long long time = std::chrono::duration_cast<std::chrono::seconds>(cur_time).count();

	for (int i = 0; i < pool_size; ++i) {
		// 获取连接
		auto conn = std::move(m_connections.front());
		m_connections.pop();

		// 为了防止触发异常做的raii
		Defer defer([this, &conn] {
			m_connections.push(std::move(conn));
			});

		// 连接未超时
		if (time - conn->m_last_oper_time <= 30) {
			continue;
		}

		try {
			auto* reply = reinterpret_cast<redisReply*>(redisCommand(conn->m_connection, "PING"));
			freeReplyObject(reply);
		}
		catch (const std::exception& e) {
			LOG_WARN("RedisPool::checkConnection ping failed: {}", e.what());
			redisFree(conn->m_connection);

			// 重新申请连接
			auto* new_conn = redisConnect(m_ip.c_str(), m_port);
			//如果连接失败，则释放连接
			if (new_conn == nullptr || new_conn->err) {
				if (new_conn) {
					LOG_WARN("RedisPool::checkConnection reconnect failed: {}", new_conn->errstr);
					redisFree(new_conn);
				}
				continue;
			}
			//如果设置密码，则进行验证
			auto reply = reinterpret_cast<redisReply*>(redisCommand(new_conn, "AUTH %s", m_password));
			//验证失败
			if (reply->type == REDIS_REPLY_ERROR) {
				LOG_WARN("RedisPool::RedisPool auth failed: {}", reply->str);
				freeReplyObject(reply);
				continue;
			}

			//验证成功
			LOG_INFO("RedisPool::RedisPool auth success");
			freeReplyObject(reply);

			conn->m_connection = new_conn;
			conn->m_last_oper_time = time;
		}
	}
}

void RedisPool::releaseConnection(std::unique_ptr<RedisConnection> connection)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (b_stop || connection == nullptr) {
		if (b_stop) {
			redisFree(connection->m_connection);
		}
		return;
	}

	// 放回连接池
	m_connections.push(std::move(connection));
	m_cv.notify_one();
}

std::unique_ptr<RedisConnection> RedisPool::getConnection()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	// 等待连接池中有可用连接或者是否关闭
	m_cv.wait(lock, [this] { return !m_connections.empty() || b_stop; });

	// 关闭返回空
	if (b_stop) return nullptr;

	// 获取连接
	auto conn = std::move(m_connections.front());
	m_connections.pop();
	return conn;
}

void RedisPool::close()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	b_stop = true;

	//释放所有连接
	while (!m_connections.empty()) {
		auto conn = std::move(m_connections.front());
		m_connections.pop();
		redisFree(conn->m_connection);
	}

	m_cv.notify_all();
}
