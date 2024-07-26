#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QObject>
#include <QQmlEngine>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "global.h"
#include "usrmgr.h"

class HttpMgr : public QObject, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
    QML_ELEMENT

signals:

    void signalShowInfo(QString);
    void signalShowError(QString);
    void signalConnectTcp(ServerInfo);
    void signalHttpFinish(ReqId id, QString res, ErrorCodes err);

public slots:

    void slotHttpFinish(ReqId id, QString res, ErrorCodes err);

public:

    static HttpMgr* Instance() {
        static HttpMgr socket;
        return &socket;
    }

    virtual ~HttpMgr();

    Q_INVOKABLE void onLoginButtonClicked(const QString& usr, const QString& pwd);
    Q_INVOKABLE void onRegisterButtonClicked(
        const QString& usr,
        const QString& email,
        const QString& pwd,
        const QString& confirm_pwd,
        const QString& varify_code);
    Q_INVOKABLE void onResetButtonClicked(
        const QString& usr,
        const QString& email,
        const QString& new_pwd,
        const QString& varify_code);
    Q_INVOKABLE void onGetVarifyCodeButtonClicked(const QString& email);

private:

    HttpMgr();
    void initHandle();
    void postHttpReq(QUrl url, QJsonObject json, ReqId req_id);

    QNetworkAccessManager m_manager;
    QMap<ReqId, std::function<void(const QJsonObject&)>> m_handlers;

};

#endif // HTTPMGR_H
