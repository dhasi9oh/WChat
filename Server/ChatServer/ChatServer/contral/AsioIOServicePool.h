#pragma once

#include <vector>
#include <boost/asio.hpp>
#include "Singleton.h"

class AsioIOServicePool :public Singleton<AsioIOServicePool>
{
	friend Singleton<AsioIOServicePool>;
public:
	using IOService = boost::asio::io_context;
	using Work = boost::asio::io_context::work;
	using WorkPtr = std::unique_ptr<Work>;

	~AsioIOServicePool();
	AsioIOServicePool(const AsioIOServicePool&) = delete;
	AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;

	// ʹ�� round-robin �ķ�ʽ����һ�� io_service
	boost::asio::io_context& getIOService();
	void stop();

private:

	AsioIOServicePool(std::size_t size = std::thread::hardware_concurrency());

	std::size_t  m_nextIOService;
	std::vector<WorkPtr> m_works;
	std::vector<std::thread> m_threads;
	std::vector<IOService> m_ioServices;
};

