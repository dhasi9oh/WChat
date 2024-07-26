#pragma once
#include <map>
#include <mutex>
#include <memory.h>
#include <boost/asio.hpp>
#include "TcpConnection.h"

class ChatServer
{
public:
	ChatServer(boost::asio::io_context& io_context, short port);
	~ChatServer();
	void clearSession(std::string);

private:

	void startAccept();
	void handleAccept(std::shared_ptr<TcpClient>, const boost::system::error_code& error);

	short m_port;
	std::mutex m_mutex;
	boost::asio::io_context& m_IOcontext;
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::map<std::string, std::shared_ptr<TcpClient>> m_sessions;
};
