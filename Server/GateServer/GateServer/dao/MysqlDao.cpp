#include "MysqlDao.h"


MysqlDao::MysqlDao()
{
    std::string host = ConfigMgr::Instance()["MYSQL"]["host"];
    std::string port = ConfigMgr::Instance()["MYSQL"]["port"];
    std::string url = host + ":" + port;
    std::string usr = ConfigMgr::Instance()["MYSQL"]["user"];
    std::string password = ConfigMgr::Instance()["MYSQL"]["password"];
    std::string database = ConfigMgr::Instance()["MYSQL"]["database"];

    m_pool = std::make_unique<MysqlPool>(url, usr, password, database);
}

bool MysqlDao::updatePassword(const std::string& username, const std::string& newPwd)
{
    auto conn = m_pool->getConnection();

    if (conn == nullptr) return false;

    Defer defer([&conn, this] { m_pool->releaseConnection(std::move(conn)); });

    try {
        //׼������ҪԤ�����SQL���
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->m_connection->prepareStatement("UPDATE user SET password = ? WHERE usr = ?"));
        //���ò���
        stmt->setString(1, newPwd);
        stmt->setString(2, username);
        //ִ��SQL���
        if (stmt->executeUpdate()) {
            return true;
        }
    }
    catch (sql::SQLException& e) {
        //��ӡ�쳣��Ϣ
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return false;
    }
}

bool MysqlDao::checkEmail(const std::string& usr, const std::string& email)
{
    auto conn = m_pool->getConnection();

    if (conn == nullptr) return false;

    Defer defer([&conn, this] { m_pool->releaseConnection(std::move(conn)); });

    try {
        //׼������ҪԤ�����SQL���
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->m_connection->prepareStatement("SELECT 1 FROM user WHERE usr = ? and email = ?"));
        //���ò���
        stmt->setString(1, usr);
        stmt->setString(2, email);
        //ִ��SQL���
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        //����ִ�н��
        return res->rowsCount();
    }
    catch (sql::SQLException& e) {
        //��ӡ�쳣��Ϣ
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
}

int MysqlDao::registerUser(const std::string& username, const std::string& email, const std::string& password)
{
    auto conn = m_pool->getConnection();

    if (conn == nullptr) return false;

    Defer defer([&conn, this] { m_pool->releaseConnection(std::move(conn)); });

    try {
        //׼������ҪԤ�����SQL���
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->m_connection->prepareStatement("CALL reg_user(?,?,?,@result)"));
        //���ò���
        stmt->setString(1, username);
        stmt->setString(2, email);
        stmt->setString(3, password);

        //ִ��SQL���
        stmt->execute();

        //��ȡִ�н��
        std::unique_ptr<sql::Statement> stmt2(conn->m_connection->createStatement());
        sql::ResultSet* res = stmt2->executeQuery("SELECT @result");

        //����ִ�н��
        if (res->next()) {
            int result = res->getInt(1);
            m_pool->releaseConnection(std::move(conn));
            return result;
        }

    }
    catch (sql::SQLException& e) {
        //��ӡ�쳣��Ϣ
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return -1;
    }
}

bool MysqlDao::checkPassword(const std::string& email, const std::string& password, UserInfo& info)
{
    auto conn = m_pool->getConnection();

    if (conn == nullptr) return false;

    Defer defer([&conn, this] { m_pool->releaseConnection(std::move(conn)); });

    try {
        //׼������ҪԤ�����SQL���
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->m_connection->prepareStatement("SELECT * FROM user WHERE email = ?"));
        //���ò���
        stmt->setString(1, email);
        //ִ��SQL���
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

        std::string pwd;

        if (res->next()) {
            pwd = res->getString("pwd");
        }

        if (pwd != password) {
            LOG_WARN("username {} pwd {} input_pwd {}", email, pwd, password);
            return false;
        }

        info.name = res->getString("name");
        info.email = res->getString("email");
        info.uid = res->getInt("uid");
        info.pwd = std::move(pwd);

        return true;
    }
    catch (sql::SQLException& e) {
        //��ӡ�쳣��Ϣ
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
}
