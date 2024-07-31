#include "MysqlDao.h"


MysqlDao::MysqlDao()
{
    std::string host = ConfigMgr::Instance()["Mysql"]["host"];
    std::string port = ConfigMgr::Instance()["Mysql"]["port"];
    std::string url = host + ":" + port;
    std::string usr = ConfigMgr::Instance()["Mysql"]["user"];
    std::string password = ConfigMgr::Instance()["Mysql"]["password"];
    std::string database = ConfigMgr::Instance()["Mysql"]["database"];

    m_pool = std::make_unique<MysqlPool>(5, url, usr, password, database);
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
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());

        return false;
    }
}

bool MysqlDao::addFriendApply(int from_uid, int to_uid)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });

    try {
        // ׼��SQL���
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("INSERT INTO friend_apply (from_uid, to_uid) values (?,?) "
            "ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"));
        pstmt->setInt(1, from_uid); // from id
        pstmt->setInt(2, to_uid);
        // ִ�и���
        int rowAffected = pstmt->executeUpdate();
        if (rowAffected < 0) {
            return false;
        }
        return true;
    }
    catch (sql::SQLException& e) {
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return false;
    }


    return true;
}

bool MysqlDao::authFriendApply(int from_uid, int to_uid)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });

    try {
        // ׼��SQL���
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("UPDATE friend_apply SET status = 1 "
            "WHERE from_uid = ? AND to_uid = ?"));
        //������������ʱfrom����֤ʱto
        pstmt->setInt(1, from_uid); // from id
        pstmt->setInt(2, to_uid);
        // ִ�и���
        int rowAffected = pstmt->executeUpdate();
        if (rowAffected < 0) {
            return false;
        }
        return true;
    }
    catch (sql::SQLException& e) {
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return false;
    }


    return true;
}

bool MysqlDao::addFriend(int from_uid, int to_uid, const std::string& back_name)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });

    try {

        //��ʼ����
        con->m_connection->setAutoCommit(false);

        // ׼����һ��SQL���, ������֤����������
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
            "VALUES (?, ?, ?) "
        ));
        //������������ʱfrom����֤ʱto
        pstmt->setInt(1, from_uid); // from id
        pstmt->setInt(2, to_uid);
        pstmt->setString(3, back_name);
        // ִ�и���
        int rowAffected = pstmt->executeUpdate();
        if (rowAffected < 0) {
            con->m_connection->rollback();
            return false;
        }

        //׼���ڶ���SQL��䣬�������뷽��������
        std::unique_ptr<sql::PreparedStatement> pstmt2(con->m_connection->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
            "VALUES (?, ?, ?) "
        ));
        //������������ʱfrom����֤ʱto
        pstmt2->setInt(1, to_uid); // from id
        pstmt2->setInt(2, from_uid);
        pstmt2->setString(3, "");
        // ִ�и���
        int rowAffected2 = pstmt2->executeUpdate();
        if (rowAffected2 < 0) {
            con->m_connection->rollback();
            return false;
        }

        // �ύ����
        con->m_connection->commit();
        std::cout << "addfriend insert friends success" << std::endl;

        return true;
    }
    catch (sql::SQLException& e) {
        // ����������󣬻ع�����
        if (con) {
            con->m_connection->rollback();
        }
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return false;
    }


    return true;
}

std::shared_ptr<UsrInfo> MysqlDao::getUserInfoByUid(int uid)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return nullptr;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });

    try {
        // ׼��SQL���
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("SELECT * FROM user WHERE uid = ?"));
        pstmt->setInt(1, uid); // ��uid�滻Ϊ��Ҫ��ѯ��uid

        // ִ�в�ѯ
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        std::shared_ptr<UsrInfo> user_ptr = nullptr;
        // ���������
        while (res->next()) {
            user_ptr.reset(new UsrInfo);
            user_ptr->pwd = res->getString("pwd");
            user_ptr->email = res->getString("email");
            user_ptr->name = res->getString("name");
            user_ptr->nick = res->getString("nick");
            user_ptr->desc = res->getString("desc");
            user_ptr->sex = res->getInt("sex");
            user_ptr->uid = uid;
            break;
        }
        return user_ptr;
    }
    catch (sql::SQLException& e) {
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return nullptr;
    }
}

std::shared_ptr<UsrInfo> MysqlDao::getUserInfoByName(const std::string& name)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return nullptr;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });

    try {
        // ׼��SQL���
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("SELECT * FROM user WHERE name = ?"));
        pstmt->setString(1, name); // ��uid�滻Ϊ��Ҫ��ѯ��uid

        // ִ�в�ѯ
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        std::shared_ptr<UsrInfo> user_ptr = nullptr;
        // ���������
        while (res->next()) {
            user_ptr.reset(new UsrInfo);
            user_ptr->pwd = res->getString("pwd");
            user_ptr->email = res->getString("email");
            user_ptr->name = res->getString("name");
            user_ptr->nick = res->getString("nick");
            user_ptr->desc = res->getString("desc");
            user_ptr->sex = res->getInt("sex");
            user_ptr->uid = res->getInt("uid");
            break;
        }
        return user_ptr;
    }
    catch (sql::SQLException& e) {
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return nullptr;
    }
}

bool MysqlDao::getApplyUsrList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list, int offset, int limit)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });


    try {
        // ׼��SQL���, ������ʼid���������������б�
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("select apply.from_uid, apply.status, user.name, "
            "user.nick, user.sex from friend_apply as apply join user on apply.from_uid = user.uid where apply.to_uid = ? "
            "and apply.id > ? order by apply.id ASC LIMIT ? "));

        pstmt->setInt(1, uid); // ��uid�滻Ϊ��Ҫ��ѯ��uid
        pstmt->setInt(2, offset); // ��ʼid
        pstmt->setInt(3, limit); //ƫ����
        // ִ�в�ѯ
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        // ���������
        while (res->next()) {
            auto name = res->getString("name");
            auto uid = res->getInt("from_uid");
            auto status = res->getInt("status");
            auto nick = res->getString("nick");
            auto sex = res->getInt("sex");
            auto apply_ptr = std::make_shared<ApplyInfo>(uid, name, "", "", nick, sex, status);
            list.push_back(apply_ptr);
        }
        return true;
    }
    catch (sql::SQLException& e) {
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return false;
    }
}

bool MysqlDao::getFriendList(int self_id, std::vector<std::shared_ptr<UsrInfo>>& user_info_list)
{
    auto con = m_pool->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        m_pool->releaseConnection(std::move(con));
        });


    try {
        // ׼��SQL���, ������ʼid���������������б�
        std::unique_ptr<sql::PreparedStatement> pstmt(con->m_connection->prepareStatement("select * from friend where self_id = ? "));

        pstmt->setInt(1, self_id); // ��uid�滻Ϊ��Ҫ��ѯ��uid

        // ִ�в�ѯ
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        // ���������
        while (res->next()) {
            auto friend_id = res->getInt("friend_id");
            auto back = res->getString("back");
            //��һ�β�ѯfriend_id��Ӧ����Ϣ
            auto user_info = getUserInfoByUid(friend_id);
            if (user_info == nullptr) {
                continue;
            }

            user_info->back = user_info->name;
            user_info_list.push_back(user_info);
        }
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }

    return true;
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
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
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
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return -1;
    }
}

bool MysqlDao::checkPassword(const std::string& email, const std::string& password, UsrInfo& info)
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
        LOG_WARN("SQLException: {} (MySQL error code: {}, SQLState: {} )", e.what(), e.getErrorCode(), e.getSQLState());
        return false;
    }
}
