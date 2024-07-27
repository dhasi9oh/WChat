#ifndef TCPMGR_H
#define TCPMGR_H

#include <QObject>
#include <QQmlEngine>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>

#include "global.h"
#include "userdata.h"

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
    //有用户添加我为好友
    void signalFriendApply(int from_id, QString name, QString desc);
    //同意添加好友
    void signalAuthRsp(int uid, QString name, QString nick, QString icon, int sex);
    //添加我同意添加申请的人为好友
    void signalAddAuthFriend(int uid, QString name, QString nick, QString icon, int sex);
    //搜索到用户
    void signalUserSearch(int uid, QString name, QString nick, QString desc, QString icon, int sex);
    //有用户发来消息
    void signalChatMsg(int from_id, QString text, bool left);

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
