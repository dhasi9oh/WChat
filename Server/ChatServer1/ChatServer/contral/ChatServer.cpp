#include "UsrMgr.h"
#include "ChatServer.h"
#include "AsioIOServicePool.h"

ChatServer::ChatServer(boost::asio::io_context& io_context, short port)
	: m_IOcontext(io_context)
	, m_port(port)
	, m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
	startAccept();
}

ChatServer::~ChatServer() {
	LOG_INFO("Server destruct listen on port : {}", m_port);
}

void ChatServer::handleAccept(std::shared_ptr<TcpClient> new_session, const boost::system::error_code& error) {
	if (!error) {
		LOG_INFO("new session accepted, sessionID is ");
		new_session->start();
		std::lock_guard<std::mutex> lock(m_mutex);
		m_sessions.insert(std::make_pair(new_session->sessionID(), new_session));
	}
	else {
		LOG_INFO("session accept failed, error is : {}", error.message());
	}

	startAccept();
}

void ChatServer::startAccept() {
	auto& io_context = AsioIOServicePool::Instance()->getIOService();
	std::shared_ptr<TcpClient> new_session = std::make_shared<TcpClient>(io_context, this);
	m_acceptor.async_accept(new_session->socket(), std::bind(&ChatServer::handleAccept, this, new_session, std::placeholders::_1));
}

void ChatServer::clearSession(std::string uuid) {

	if (m_sessions.find(uuid) != m_sessions.end()) {
		//移除用户和session的关联
		UsrMgr::Instance()->rmUserSession(m_sessions[uuid]->getUserID());
	}

	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_sessions.erase(uuid);
	}

}
