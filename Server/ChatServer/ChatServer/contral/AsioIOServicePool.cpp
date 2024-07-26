#include "AsioIOServicePool.h"
#include <iostream>
using namespace std;

AsioIOServicePool::AsioIOServicePool(std::size_t size)
	: m_ioServices(size)
	, m_works(size)
	, m_nextIOService(0)
{
	for (std::size_t i = 0; i < size; ++i) {
		m_works[i] = std::unique_ptr<Work>(new Work(m_ioServices[i]));
	}

	//遍历多个ioservice，创建多个线程，每个线程内部启动ioservice
	for (std::size_t i = 0; i < m_ioServices.size(); ++i) {
		m_threads.emplace_back([this, i]() {
			m_ioServices[i].run();
			});
	}
}

AsioIOServicePool::~AsioIOServicePool() {
	std::cout << "AsioIOServicePool destruct" << endl;
}

boost::asio::io_context& AsioIOServicePool::getIOService() {
	auto& service = m_ioServices[m_nextIOService++];
	if (m_nextIOService == m_ioServices.size()) {
		m_nextIOService = 0;
	}
	return service;
}

void AsioIOServicePool::stop() {
	//因为仅仅执行work.reset并不能让iocontext从run的状态中退出
	//当iocontext已经绑定了读或写的监听事件后，还需要手动stop该服务。
	for (auto& work : m_works) {
		//把服务先停止
		work->get_io_context().stop();
		work.reset();
	}

	for (auto& t : m_threads) {
		t.join();
	}
}