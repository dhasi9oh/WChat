#pragma once

#include "Loger.h"
#include "const.h"
#include "MsgNode.h"
#include "ChatServer.h"
#include "LogicSystem.h"

#include <queue>
#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class ChatServer;
class LogicSystem;

class TcpClient : public std::enable_shared_from_this<TcpClient>
{
public:

	TcpClient(boost::asio::io_context& io_context, ChatServer* server);
	~TcpClient();

	std::string& sessionID();
	boost::asio::ip::tcp::socket& socket();

	void setUserID(int uid);
	int getUserID() const;

	//������յ���ҵ��
	void start();
	//�رո�����
	void close();
	//��������
	void send(const std::string& message, int msg_id);
	void send(const char* message, int length, int msg_id);
	//����һ��ָ���Լ�������ָ��
	std::shared_ptr<TcpClient> sharedSelf();
	//��ȡ����
	void asyncReadBody(int len);
	//��ȡͷ��
	//ͷ�� = 2���ֽ�id + 2���ֽ���Ϣ����
	void asyncReadHeader(int len);

private:

	void asyncReadFull(int len, std::function<void(const boost::system::error_code&, size_t)> handler);
	void asyncReadLength(int read_len, int total_len, std::function<void(const boost::system::error_code&, size_t)> handler);

	void handleWrite(const boost::system::error_code& ec, std::shared_ptr<TcpClient> shared_self);

	bool b_stop;
	//���ݿ����û���Ψһ��ʶ��
	int m_uid;
	//���ڴ��е�Ψһ��ʶ��
	std::string m_sessionID;
	//������ʶ����������ϵ�������𣬵��û�û�е�¼�Ż����ֳ�����
	std::mutex m_mutex;
	boost::asio::ip::tcp::socket m_socket;
	//���ջ�����
	char m_buf[MAX_LENGTH];
	//�����ķ�����
	ChatServer*m_server;
	//ͷ���Ƿ�������
	bool b_headerParse;
	//�յ�����Ϣ
	std::shared_ptr<RecvMsgNode> m_recvMsgNode;
	//�յ���Ϣ��ͷ����Ϣ
	std::shared_ptr<RecvMsgNode> m_recvHeaderNode;
	//�����͵���Ϣ����
	std::queue<std::shared_ptr<SendMsgNode>> m_sendMsgQueue;

};

class LogicNode
{
	friend class LogicSystem;

public:

	LogicNode(std::shared_ptr<TcpClient> session, std::shared_ptr<RecvMsgNode> node);

private:

	std::shared_ptr<TcpClient> m_session;
	std::shared_ptr<RecvMsgNode> m_recvNode;

};