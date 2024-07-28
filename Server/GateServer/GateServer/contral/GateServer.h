#pragma once
#include <string>
#include "const.h"

class GateServer: public std::enable_shared_from_this<GateServer>
{
public:
	GateServer(boost::asio::io_context& ioc, unsigned short& port);
	void start();
private:
	boost::asio::ip::tcp::acceptor  m_acceptor;
	boost::asio::io_context& m_iocntext;
	
};

