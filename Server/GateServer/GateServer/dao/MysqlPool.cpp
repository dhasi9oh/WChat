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
			// ��ȡ��ǰʱ��
			auto cur_time = std::chrono::system_clock::now().time_since_epoch();
			long long time = std::chrono::duration_cast<std::chrono::seconds>(cur_time).count();

			// �������ݿ�����
			auto drive = sql::mysql::get_mysql_driver_instance();
			auto con = std::make_unique<SqlConnection>(drive->connect(m_url, m_user, m_password), time);
			con->m_connection->setSchema(m_database);
			m_connections.push(std::move(con));
		}

		m_thread = std::thread(
			[this] {
				// ��ʱ��������Ƿ�ʱ
				while (!b_stop) {
					checkConnection();
					// ÿ��60����һ��
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
	//��ȡ��ǰʱ��
	auto cur_time = std::chrono::system_clock::now().time_since_epoch();
	long long time = std::chrono::duration_cast<std::chrono::seconds>(cur_time).count();

	for (int i = 0; i < pool_size; ++i) {
		// ��ȡ����
		auto conn = std::move(m_connections.front());
		m_connections.pop();

		// Ϊ�˷�ֹ�����쳣����raii
		Defer defer([this, &conn] {
			m_connections.push(std::move(conn));
			});
	
		// ����δ��ʱ
		if (time - conn->m_last_oper_time <= 5) {
			continue;
		}

		try {
			// ִ��һ����ѯ���, ��ֹ���ӳ�ʱ
			std::unique_ptr<sql::Statement> stmt(conn->m_connection->createStatement());
			stmt->executeQuery("SELECT 1");
			conn->m_last_oper_time = time;
		}
		catch (sql::SQLException& e) {
			// ��ӡ������Ϣ
			std::cerr << "MysqlPool::checkConnection() - " << e.what() << std::endl;

			// �������ݿ�����
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

	// �Ż����ӳ�
	m_connections.push(std::move(connection));
	m_cv.notify_one();
}

std::unique_ptr<SqlConnection> MysqlPool::getConnection()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	// �ȴ����ӳ����п������ӻ����Ƿ�ر�
	m_cv.wait(lock, [this] { return !m_connections.empty() || b_stop; });

	// �رշ��ؿ�
	if (b_stop) return nullptr;

	// ��ȡ����
	auto conn = std::move(m_connections.front());
	m_connections.pop();
	return conn;
}

void MysqlPool::close()
{
	b_stop = true;
	m_cv.notify_all();
}
