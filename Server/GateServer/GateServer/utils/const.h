#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/system/error_code.hpp>

#include "Loger.h"


constexpr char CONFIG_FILE_NAME[] = "config.ini";

class Defer {
public:

	Defer(std::function<void()> func) : m_func(func) {}

	~Defer() { m_func(); }

private:

	std::function<void()> m_func;

};

constexpr const char CODEPREFIX[] = "code_";

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