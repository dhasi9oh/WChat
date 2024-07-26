#include "tcpmgr.h"

void TcpMgr::slotTcpConnect(ServerInfo info)
{
    m_host = info.Host;
    m_port = static_cast<uint16_t>(info.Port.toUInt());
    m_socket.connectToHost(m_host, m_port);
}

void TcpMgr::slotSendData(ReqId reqId, QString data)
{
    uint16_t id = reqId;

    // 将字符串转换为UTF-8编码的字节数组
    QByteArray dataBytes = data.toUtf8();

    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(data.size());

    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);

    // 写入ID和长度
    out << id << len;

    // 添加字符串数据
    block.append(data.toUtf8());

    // 发送数据
    m_socket.write(block);
    qDebug() << "tcp mgr send byte data is " << block ;
}

TcpMgr::~TcpMgr()
{

}

TcpMgr::TcpMgr() :
    m_host(""),
    m_port(0),
    m_messageId(0),
    m_messageLen(0),
    b_recvPending(false)
{
    QObject::connect(&m_socket, &QTcpSocket::readyRead, [&]() {
        // 当有数据可读时，读取所有数据
        // 读取所有数据并追加到缓冲区
        m_buf.append(m_socket.readAll());

        QDataStream stream(&m_buf, QIODevice::ReadOnly);

        forever {
            //先解析头部
            if(!b_recvPending){
                // 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
                if (m_buf.size() < static_cast<int>(sizeof(quint16) * 2)) {
                    return; // 数据不够，等待更多数据
                }

                // 预读取消息ID和消息长度，但不从缓冲区中移除
                stream >> m_messageId >> m_messageLen;

                //将buffer 中的前四个字节移除
                m_buf = m_buf.mid(sizeof(quint16) * 2);

                // 输出读取的数据
                qDebug() << "Message ID:" << m_messageId << ", Length:" << m_messageLen;

            }

            //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
            if(m_buf.size() < m_messageLen){
                b_recvPending = true;
                return;
            }

            b_recvPending = false;
            // 读取消息体
            QByteArray messageBody = m_buf.mid(0, m_messageLen);
            qDebug() << "receive body msg is " << messageBody ;

            m_buf = m_buf.mid(m_messageLen);
            handleMsg(ReqId(m_messageId), m_messageLen, messageBody);
        }
    });

    QObject::connect(&m_socket, &QTcpSocket::errorOccurred, [&](QAbstractSocket::SocketError socketError) {
        qDebug() << "Error:" << m_socket.errorString();
        switch (socketError) {
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "Connection Refused!";
            emit signalConnectSuccess(false);
            break;
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() << "Remote Host Closed Connection!";
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "Host Not Found!";
            emit signalConnectSuccess(false);
            break;
        case QAbstractSocket::SocketTimeoutError:
            qDebug() << "Connection Timeout!";
            emit signalConnectSuccess(false);
            break;
        case QAbstractSocket::NetworkError:
            qDebug() << "Network Error!";
            break;
        default:
            qDebug() << "Other Error!";
            break;
        }
    });

    connect(this, &TcpMgr::signalSendData, this, &TcpMgr::slotSendData);
    connect(HttpMgr::Instance(), &HttpMgr::signalConnectTcp, this, &TcpMgr::slotTcpConnect);
    connect(&m_socket, &QTcpSocket::connected, [this] {
        QJsonObject jsonObj;
        jsonObj["uid"] = UsrMgr::Instance()->getUsrInfo()._uid;
        jsonObj["token"] = UsrMgr::Instance()->getToken();

        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        slotSendData(ReqId::ID_CHAT_LOGIN, jsonString);
    });

    //注册消息
    initHandle();
}

void TcpMgr::initHandle()
{
    m_handlers.insert(ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << "data jsonobj is " << jsonObj;

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Login Failed, err is Json Parse Err" << err;
            emit signalLoginFailed(err);
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Login Failed, err is " << err;
            emit signalLoginFailed(err);
            return;
        }

        auto uid = jsonObj["uid"].toInt();
        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        auto user_info = UserInfo(uid, name, nick, icon, sex);

        UsrMgr::Instance()->setUsrInfo(user_info);
        UsrMgr::Instance()->setToken(jsonObj["token"].toString());
        if (jsonObj.contains("apply_list")) {
           UsrMgr::Instance()->appendApplyList(jsonObj["apply_list"].toArray());
        }

        //添加好友列表
        if (jsonObj.contains("friend_list")) {
           UsrMgr::Instance()->appendFriendList(jsonObj["friend_list"].toArray());
        }

        emit signalSwichChatdlg();
        });


    // m_handlers.insert(ID_SEARCH_USER_RSP, [this](ReqId id, int len, QByteArray data) {
    //     Q_UNUSED(len);
    //     qDebug() << "handle id is " << id << " data is " << data;
    //     // 将QByteArray转换为QJsonDocument
    //     QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    //     // 检查转换是否成功
    //     if (jsonDoc.isNull()) {
    //         qDebug() << "Failed to create QJsonDocument.";
    //         return;
    //     }

    //     QJsonObject jsonObj = jsonDoc.object();

    //     if (!jsonObj.contains("error")) {
    //         int err = ErrorCodes::ERR_JSON;
    //         qDebug() << "Login Failed, err is Json Parse Err" << err;

    //         emit signalUserSearch(nullptr);
    //         return;
    //     }

    //     int err = jsonObj["error"].toInt();
    //     if (err != ErrorCodes::SUCCESS) {
    //         qDebug() << "Login Failed, err is " << err;
    //         emit signalUserSearch(nullptr);
    //         return;
    //     }
    //     auto search_info = std::make_shared<SearchInfo>(
    //         jsonObj["uid"].toInt(), jsonObj["name"].toString(),
    //         jsonObj["nick"].toString(), jsonObj["desc"].toString(),
    //         jsonObj["sex"].toInt(), jsonObj["icon"].toString());

    //     emit signalUserSearch(search_info);
    //     });

    //服务端转发的添加好友申请
    m_handlers.insert(ID_NOTIFY_ADD_FRIEND_REQ, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Login Failed, err is Json Parse Err" << err;

            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Login Failed, err is " << err;
            return;
        }

        int applyuid = jsonObj["applyuid"].toInt();
        QString name = jsonObj["name"].toString();
        QString desc = jsonObj["desc"].toString();
        AddFriendApply apply_info(applyuid, name, desc);

        emit signalFriendApply(applyuid, name, desc);
        });

    //服务端转发的添加好友认证
    m_handlers.insert(ID_NOTIFY_AUTH_FRIEND_REQ, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        int from_uid = jsonObj["fromuid"].toInt();
        QString name = jsonObj["name"].toString();
        QString nick = jsonObj["nick"].toString();
        QString icon = jsonObj["icon"].toString();
        int sex = jsonObj["sex"].toInt();

        auto auth_info = AuthInfo(from_uid, name, nick, icon, sex);

        emit signalAddAuthFriend(auth_info);
        });

    m_handlers.insert(ID_ADD_FRIEND_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Add Friend Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Add Friend Failed, err is " << err;
            return;
        }

        qDebug() << "Add Friend Success ";
        });


    m_handlers.insert(ID_AUTH_FRIEND_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Auth Friend Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        auto uid = jsonObj["uid"].toInt();
        auto rsp = AuthRsp(uid, name, nick, icon, sex);
        emit signalAuthRsp(rsp);

        qDebug() << "Auth Friend Success ";
        });


    m_handlers.insert(ID_TEXT_CHAT_MSG_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Auth Friend Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        qDebug() << "Receive Text Chat Rsp Success ";
        });
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
    auto find_iter =  m_handlers.find(id);
    if(find_iter == m_handlers.end()){
        qDebug()<< "not found id ["<< id << "] to handle";
        return ;
    }

    find_iter.value()(id,len,data);
}

