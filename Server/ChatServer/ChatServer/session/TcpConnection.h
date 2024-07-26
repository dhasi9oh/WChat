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

	//处理接收到的业务
	void start();
	//关闭该连接
	void close();
	//发送数据
	void send(const std::string& message, int msg_id);
	void send(const char* message, int length, int msg_id);
	//生成一个指向自己的智能指针
	std::shared_ptr<TcpClient> sharedSelf();
	//读取数据
	void asyncReadBody(int len);
	//读取头部
	//头部 = 2个字节id + 2个字节消息长度
	void asyncReadHeader(int len);

private:

	void asyncReadFull(int len, std::function<void(const boost::system::error_code&, size_t)> handler);
	void asyncReadLength(int read_len, int total_len, std::function<void(const boost::system::error_code&, size_t)> handler);

	void handleWrite(const boost::system::error_code& ec, std::shared_ptr<TcpClient> shared_self);

	bool b_stop;
	//数据库中用户的唯一标识符
	int m_uid;
	//在内存中的唯一标识符
	std::string m_sessionID;
	//两个标识符在这里体系不出区别，当用户没有登录才会体现出区别
	std::mutex m_mutex;
	boost::asio::ip::tcp::socket m_socket;
	//接收缓冲区
	char m_buf[MAX_LENGTH];
	//所属的服务器
	ChatServer*m_server;
	//头部是否解析完毕
	bool b_headerParse;
	//收到的消息
	std::shared_ptr<RecvMsgNode> m_recvMsgNode;
	//收到消息的头部信息
	std::shared_ptr<RecvMsgNode> m_recvHeaderNode;
	//待发送的消息队列
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