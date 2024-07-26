#include "usrmgr.h"


UsrMgr::~UsrMgr()
{

}

QString UsrMgr::getToken() const
{
    return m_token;
}

void UsrMgr::setToken(const QString &token)
{
    m_token = token;
}

UserInfo UsrMgr::getUsrInfo()
{
    return m_userInfo;
}

void UsrMgr::setUsrInfo(const UserInfo& usr_info)
{
    m_userInfo = usr_info;
}

void UsrMgr::appendApply(const ApplyInfo &info)
{
    m_applyList.push_back(info);
    emit addApply(info._name, info._desc, info._icon, info._nick, info._sex, info._uid, info._status);
}

void UsrMgr::appendApplyList(const QJsonArray &array)
{
    for (const QJsonValue& value : array) {
        auto name = value["name"].toString();
        auto desc = value["desc"].toString();
        auto icon = value["icon"].toString();
        auto nick = value["nick"].toString();
        auto sex = value["sex"].toInt();
        auto uid = value["uid"].toInt();
        auto status = value["status"].toInt();

        auto info = ApplyInfo(uid, name, desc, icon, nick, sex, status);

        appendApply(info);
    }
}

void UsrMgr::appendFriend(const AuthInfo &info)
{
    FriendInfo friend_info(info);
    appendFriend(info);
}

void UsrMgr::appendFriend(const FriendInfo &info)
{
    m_friendList.push_back(info);
    emit addFriend(info._name, info._icon, info._nick, info._sex, info._uid);
}

void UsrMgr::appendFriendList(const QJsonArray &array)
{
    for (const QJsonValue& value : array) {
        auto name = value["name"].toString();
        auto desc = value["desc"].toString();
        auto icon = value["icon"].toString();
        auto nick = value["nick"].toString();
        auto sex = value["sex"].toInt();
        auto uid = value["uid"].toInt();
        auto back = value["back"].toString();

        auto info = FriendInfo(uid, name, nick, icon, sex, desc, back);
        appendFriend(info);
    }
}

UsrMgr::UsrMgr()
{
}


