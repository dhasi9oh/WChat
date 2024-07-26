#ifndef USRMGR_H
#define USRMGR_H

#include <QObject>
#include <QQmlEngine>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "userdata.h"

class UsrMgr : public QObject
{
    Q_OBJECT
    QML_ELEMENT

signals:

    void addApply(QString name, QString desc, QString icon, QString nick, int sex, int uid, int status);
    void addFriend(QString name, QString icon, QString nick, int sex, int uid);

public:

    static UsrMgr* Instance() {
        static UsrMgr usr_mgr;
        return &usr_mgr;
    }

    virtual ~UsrMgr();

    QString getToken() const;
    void setToken(const QString& token);

    UserInfo getUsrInfo();
    void setUsrInfo(const UserInfo& usr_info);

    void appendApply(const ApplyInfo &info);
    void appendApplyList(const QJsonArray& array);

    void appendFriend(const AuthInfo &info);
    void appendFriend(const FriendInfo &info);
    void appendFriendList(const QJsonArray& array);


private:

    UsrMgr();

    QString m_token;
    UserInfo m_userInfo;
    std::vector<ApplyInfo> m_applyList;
    std::vector<FriendInfo> m_friendList;

};

#endif // USRMGR_H
