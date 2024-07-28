#include "GateServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

GateServer::GateServer(boost::asio::io_context& ioc, unsigned short& port)
	: m_iocntext(ioc)
	, m_acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {

}

void GateServer::start()
{	
	auto self = shared_from_this();
	auto& io_context = AsioIOServicePool::Instance()->getIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);
	m_acceptor.async_accept(new_con->getSocket(), [self, new_con](boost::beast::error_code ec) {
		try {
			//出错则放弃这个连接，继续监听新链接
			if (ec) {
				self->start();
				return;
			}

			//处理新链接，创建HpptConnection类管理新连接
			new_con->start();
			//继续监听
			self->start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->start();
		}
	});
}


