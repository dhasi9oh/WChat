#pragma once

#include <jsoncpp/json/json.h>

#include "data.h"
#include "MysqlDao.h"
#include "RedisDao.h"
#include "message.pb.h"
#include "TcpConnection.h"
#include "ChatGrpcClient.h"

class TcpClient;
class LogicNode;
using FuncCallback = std::function<void(std::shared_ptr<TcpClient>, const short& msg_id, const std::string&)>;

class LogicSystem : public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;

public:

    ~LogicSystem();
    //将用户请求添加到堵塞队列
    void postMsgToQue(std::shared_ptr<LogicNode> node);

private:

    LogicSystem();
    //处理所有用户的消息函数
    void dealMsg();
    //绑定一些回调函数
    void registerCallBacks();
    //登录请求
    void loginHandler(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //搜索陌生人请求
    void searchInfo(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //添加好友申请
    void addFriendApply(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //好友申请认证
    void authFriendApply(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //发送消息
    void dealChatTextMsg(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //检查uid的正确性
    bool isPureDigit(const std::string& uid);
    //获取用户的信息通过uid
    void getUserInfoByUid(const std::string& uid, Json::Value& info);
    //获取用户的信息通过Name
    void getUserInfoByName(const std::string& name, Json::Value& info);
    //获取用户的基础信息
    bool getUserBaseInfo(const std::string& base_key, int uid, std::shared_ptr<UsrInfo> &info);
    //获取好友申请列表
    bool getFriendApplyListInfo(int uid, std::vector<std::shared_ptr<ApplyInfo>> &info_list);
    //获取好友列表
    bool getFriendListInfo(int uid, std::vector<std::shared_ptr<UsrInfo>>& info_list);

    bool b_stop;
    std::mutex m_mutex;
    std::thread m_thread;
    std::condition_variable m_cv;
    std::map<int, FuncCallback> m_callBackMap;
    std::queue<std::shared_ptr<LogicNode>> m_msgQue;

};