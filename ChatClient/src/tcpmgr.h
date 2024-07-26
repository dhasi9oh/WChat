#ifndef TCPMGR_H
#define TCPMGR_H

#include <QObject>
#include <QQmlEngine>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>

#include "global.h"
#include "usrmgr.h"
#include "httpmgr.h"
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
    //
    void signalUserSearch(SearchInfo);
    void signalFriendApply(int from_id, QString name, QString desc);
    void signalAddAuthFriend(AuthInfo);
    void signalAuthRsp(AuthRsp);

public slots:

    void slotTcpConnect(ServerInfo);
    void slotSendData(ReqId reqId, QString data);

public:

    static TcpMgr* Instance() {
        static TcpMgr socket;
        return &socket;
    }

    virtual ~TcpMgr();

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
