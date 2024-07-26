#ifndef TCPMGR_H
#define TCPMGR_H

#include <QObject>
#include <QQmlEngine>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>

#include "global.h"

class TcpMgr : public QObject
{
    Q_OBJECT
    QML_ELEMENT

signals:

    //连接结果信号
    void signalConnectSuccess(bool bsuccess);
    //发送数据信号
    void signalSendData(ReqId reqId, QString data);
    //跳转聊天窗口
    void signalSwichChatdlg();
    //tcp登录到服务器以后服务器没有token
    void signalLoginFailed(int);
    //void signalUserSearch(SearchInfo);
    void signalFriendApply(int from_id, QString name, QString desc);
    void signalAuthRsp(int uid, QString name, QString nick, QString icon, int sex);
    void signalAddAuthFriend(int uid, QString name, QString nick, QString icon, int sex);

public slots:

    void slotTcpConnect(ServerInfo);
    void slotSendData(ReqId reqId, QString data);

public:

    static TcpMgr* Instance() {
        static TcpMgr socket;
        return &socket;
    }

    virtual ~TcpMgr();

    Q_INVOKABLE void addFriend(int from_id, const QString& apply_name, const QString& back_name, int to_uid);
    Q_INVOKABLE void authFriend(int from_id, int to_uid, const QString& back_name);
    Q_INVOKABLE void sendChatTextMsg(int from_id, int to_uid, const QString& text);

private:

    TcpMgr();
    //报文响应初始化
    void initHandle();
    void handleMsg(ReqId id, int len, QByteArray data);

    bool b_recvPending;
    QString m_host;
    quint16 m_port;
    QByteArray m_buf;
    QTcpSocket m_socket;
    quint16 m_messageId;
    quint16 m_messageLen;
    QMap<int, std::function<void(ReqId id, int len, QByteArray data)>> m_handlers;

};

#endif // TCPMGR_H
