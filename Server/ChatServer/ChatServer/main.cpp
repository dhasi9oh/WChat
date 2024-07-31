
#include <csignal>
#include <thread>
#include <mutex>
#include "RedisDao.h"
#include "ConfigMgr.h"
#include "ChatServer.h"
#include "LogicSystem.h"
#include "ChatServiceImpl.h"
#include "AsioIOServicePool.h"


int main()
{
	RedisDao::Instance();
	auto& cfg = ConfigMgr::Instance();
	auto server_name = cfg["SelfServer"]["name"];
	try {
		auto pool = AsioIOServicePool::Instance();
		//����¼������Ϊ0
		RedisDao::Instance()->HSet(LOGIN_COUNT, server_name, "0");

		//����һ��GrpcServer

		std::string server_address(cfg["SelfServer"]["host"] + ":" + cfg["SelfServer"]["rpc_port"]);
		ChatServiceImpl service;
		grpc::ServerBuilder builder;
		// �����˿ں���ӷ���
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		// ����������gRPC������
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "RPC Server listening on " << server_address << std::endl;

		//��������һ���̴߳���grpc����
		std::thread  grpc_server_thread([&server]() {
			server->Wait();
			});

		boost::asio::io_context io_context;
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
		signals.async_wait([&io_context, pool, &server](auto, auto) {
			io_context.stop();
			pool->stop();
			server->Shutdown();
			});
		auto port_str = cfg["SelfServer"]["port"];
		ChatServer s(io_context, atoi(port_str.c_str()));
		io_context.run();
		RedisDao::Instance()->HDel(LOGIN_COUNT, server_name);
		RedisDao::Instance()->Close();
		grpc_server_thread.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		RedisDao::Instance()->HDel(LOGIN_COUNT, server_name);
		RedisDao::Instance()->Close();
	}

}