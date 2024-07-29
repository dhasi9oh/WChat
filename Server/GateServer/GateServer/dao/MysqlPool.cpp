#include "MysqlPool.h"


MysqlPool::MysqlPool(int size, const std::string& url, const std::string& user, const std::string& password, const std::string& database)
	: m_size(size)
	, m_url(url)
	, m_user(user)
	, m_password(password)
	, m_database(database)
	, b_stop(false)
{
	try {
		for (int i = 0; i < size; ++i) {
			// 获取当前时间
			auto cur_time = std::chrono::system_clock::now().time_since_epoch();
			long long time = std::chrono::duration_cast<std::chrono::seconds>(cur_time).count();

			// 创建数据库连接
			auto drive = sql::mysql::get_mysql_driver_instance();
			auto con = std::make_unique<SqlConnection>(drive->connect(m_url, m_user, m_password), time);
			con->m_connection->setSchema(m_database);
			m_connections.push(std::move(con));
		}

		m_thread = std::thread(
			[this] {
				// 定时检查连接是否超时
				while (!b_stop) {
					checkConnection();
					// 每隔60秒检查一次
					std::this_thread::sleep_for(std::chrono::seconds(60));
				}
			}
		);

		m_thread.detach();
	}
	catch (sql::SQLException& e) {
		std::cerr << "MysqlPool::MysqlPool() - " << e.what() << std::endl;
	}
}

MysqlPool::~MysqlPool()
{
	close();
}

void MysqlPool::checkConnection()
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
		if (time - conn->m_last_oper_time <= 5) {
			continue;
		}

		try {
			// 执行一个查询语句, 防止连接超时
			std::unique_ptr<sql::Statement> stmt(conn->m_connection->createStatement());
			stmt->executeQuery("SELECT 1");
			conn->m_last_oper_time = time;
		}
		catch (sql::SQLException& e) {
			// 打印错误信息
			std::cerr << "MysqlPool::checkConnection() - " << e.what() << std::endl;

			// 创建数据库连接
			auto drive = sql::mysql::get_mysql_driver_instance();
			auto new_con = drive->connect(m_url, m_user, m_password);
			new_con->setSchema(m_database);
			conn->m_connection.reset(new_con);
			conn->m_last_oper_time = time;
		}
	}
}

void MysqlPool::releaseConnection(std::unique_ptr<SqlConnection> connection)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (b_stop) return;

	// 放回连接池
	m_connections.push(std::move(connection));
	m_cv.notify_one();
}

std::unique_ptr<SqlConnection> MysqlPool::getConnection()
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

void MysqlPool::close()
{
	b_stop = true;
	m_cv.notify_all();
}
