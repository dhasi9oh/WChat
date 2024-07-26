#pragma once

#include "data.h"
#include "Loger.h"
#include "Singleton.h"
#include "ConfigMgr.h"

#include <functional>

enum MSG_IDS {
	MSG_CHAT_LOGIN = 1005, //�û���½
	MSG_CHAT_LOGIN_RSP = 1006, //�û���½�ذ�
	ID_SEARCH_USER_REQ = 1007, //�û���������
	ID_SEARCH_USER_RSP = 1008, //�����û��ذ�
	ID_ADD_FRIEND_REQ = 1009, //������Ӻ�������
	ID_ADD_FRIEND_RSP = 1010, //������Ӻ��ѻظ�
	ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //֪ͨ�û���Ӻ�������
	ID_AUTH_FRIEND_REQ = 1013,  //��֤��������
	ID_AUTH_FRIEND_RSP = 1014,  //��֤���ѻظ�
	ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //֪ͨ�û���֤��������
	ID_TEXT_CHAT_MSG_REQ = 1017, //�ı�������Ϣ����
	ID_TEXT_CHAT_MSG_RSP = 1018, //�ı�������Ϣ�ظ�
	ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //֪ͨ�û��ı�������Ϣ
};



// Defer��
class Defer {
public:
	// ����һ��lambda���ʽ���ߺ���ָ��
	Defer(std::function<void()> func) : func_(func) {}

	// ����������ִ�д���ĺ���
	~Defer() {
		func_();
	}

private:
	std::function<void()> func_;
};


enum ErrorCodes {
	Success = 0,
	Error_Json = 1001,  //Json��������
	RPCFailed = 1002,  //RPC�������
	VarifyExpired = 1003, //��֤�����
	VarifyCodeErr = 1004, //��֤�����
	UserExist = 1005,       //�û��Ѿ�����
	PasswdErr = 1006,    //�������
	EmailNotMatch = 1007,  //���䲻ƥ��
	PasswdUpFailed = 1008,  //��������ʧ��
	PasswdInvalid = 1009,   //�������ʧ��
	TokenInvalid = 1010,   //TokenʧЧ
	UidInvalid = 1011,  //uid��Ч
};


constexpr const int HEAD_ID_LEN = 2;
constexpr const int HEAD_DATA_LEN = 2;
constexpr const int HEAD_TOTAL_LEN = 4;

constexpr const int MAX_LENGTH = 2048;
constexpr const int MAX_SEND_QUEUE_SIZE = 1000;
constexpr const char USERIPPREFIX[] = "uip_";
constexpr const char USERTOKENPREFIX[] = "utoken_";
constexpr const char IPCOUNTPREFIX[] = "ipcount_";
constexpr const char USER_BASE_INFO[] = "ubaseinfo_";
constexpr const char LOGIN_COUNT[] = "logincount";
constexpr const char NAME_INFO[] = "nameinfo_";
