#pragma once

#include "const.h"

#include <cstring>
#include <boost/asio.hpp>

class LogicSystem;

// ���࣬��Ϣ������
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

	//ָ������
	char* data_ptr;
	//���ݴ�С
	size_t size;
	//��������С
	size_t total;
};

// ������Ϣ�ڵ�
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

// ������Ϣ�ڵ�
class SendMsgNode : public MsgNode
{
	friend class LogicSystem;

public:

	SendMsgNode(const char* ptr, size_t size, short msg_id);

private:

	short m_msg_id;

};