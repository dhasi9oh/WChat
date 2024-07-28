#pragma once

#include "const.h"

#include <cstring>
#include <boost/asio.hpp>

class LogicSystem;

// 基类，消息缓冲区
class MsgNode
{
public:

	MsgNode(size_t size)
		: total(0)
		, size(size)
		, data_ptr(new char[size + 1]())
	{
		data_ptr[size] = '\0';
	}

	~MsgNode()
	{
		delete[] data_ptr;
	}

	void clear()
	{
		size = 0;
		std::memset(data_ptr, 0, total);
	}

	//指向数据
	char* data_ptr;
	//数据大小
	size_t size;
	//缓冲区大小
	size_t total;
};

// 接收消息节点
class RecvMsgNode : public MsgNode
{
	friend class LogicSystem;

public:

	RecvMsgNode(size_t size, short msg_id)
		: MsgNode(size)
		, m_msg_id(msg_id)
	{
	}

private:

	short m_msg_id;

};

// 发送消息节点
class SendMsgNode : public MsgNode
{
	friend class LogicSystem;

public:

	SendMsgNode(const char* ptr, size_t size, short msg_id);

private:

	short m_msg_id;

};