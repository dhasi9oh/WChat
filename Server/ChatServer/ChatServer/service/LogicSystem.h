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
    //���û�������ӵ���������
    void postMsgToQue(std::shared_ptr<LogicNode> node);

private:

    LogicSystem();
    //���������û�����Ϣ����
    void dealMsg();
    //��һЩ�ص�����
    void registerCallBacks();
    //��¼����
    void loginHandler(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //����İ��������
    void searchInfo(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //��Ӻ�������
    void addFriendApply(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //����������֤
    void authFriendApply(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //������Ϣ
    void dealChatTextMsg(std::shared_ptr<TcpClient> session, const short& msg_id, const std::string& message);
    //���uid����ȷ��
    bool isPureDigit(const std::string& uid);
    //��ȡ�û�����Ϣͨ��uid
    void getUserInfoByUid(const std::string& uid, Json::Value& info);
    //��ȡ�û�����Ϣͨ��Name
    void getUserInfoByName(const std::string& name, Json::Value& info);
    //��ȡ�û��Ļ�����Ϣ
    bool getUserBaseInfo(const std::string& base_key, int uid, std::shared_ptr<UsrInfo> &info);
    //��ȡ���������б�
    bool getFriendApplyListInfo(int uid, std::vector<std::shared_ptr<ApplyInfo>> &info_list);
    //��ȡ�����б�
    bool getFriendListInfo(int uid, std::vector<std::shared_ptr<UsrInfo>>& info_list);

    bool b_stop;
    std::mutex m_mutex;
    std::thread m_thread;
    std::condition_variable m_cv;
    std::map<int, FuncCallback> m_callBackMap;
    std::queue<std::shared_ptr<LogicNode>> m_msgQue;

};