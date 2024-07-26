#pragma once

#include <queue>
#include <mutex>
#include <grpcpp/grpcpp.h>
#include <condition_variable>

#include "Singleton.h"
#include "message.pb.h"
#include "message.grpc.pb.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::AddFriendReq;
using message::AddFriendRsp;

using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::ChatService;


class ChatGrpcClientPool
{
public:

	ChatGrpcClientPool(size_t size, std::string host, std::string port)
		: m_size(size), m_host(host), m_port(port)
	{
		for (size_t i = 0; i < size; ++i) {

			std::shared_ptr<grpc::Channel> ptr =
				grpc::CreateChannel(m_host + ":" + m_port, grpc::InsecureChannelCredentials());

			m_pool.push(ChatService::NewStub(ptr));
		}
	}

	// 归还grpc的连接
	void releaseStub(std::unique_ptr<ChatService::Stub> connection)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (b_stop) return;

		// 放回连接池
		m_pool.push(std::move(connection));
		m_cv.notify_one();
	}

	// 获取grpc的连接
	std::unique_ptr<ChatService::Stub> getStub()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		// 等待连接池中有可用连接或者是否关闭
		m_cv.wait(lock, [this] { return !m_pool.empty() || b_stop; });

		// 关闭返回空
		if (b_stop) return nullptr;

		// 获取连接
		auto conn = std::move(m_pool.front());
		m_pool.pop();
		return conn;
	}

	// 关闭grpc连接池
	void close()
	{
		b_stop = true;
		m_cv.notify_all();
	}

private:

	bool b_stop;
	size_t m_size;
	std::string m_host;
	std::string m_port;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::queue<std::unique_ptr<ChatService::Stub>> m_pool;

};

class ChatGrpcClient :public Singleton<ChatGrpcClient>
{
	friend class Singleton<ChatGrpcClient>;

public:

	AddFriendRsp NotifyAddFriend(const AddFriendReq& req);

private:

	ChatGrpcClient();

	std::unique_ptr<ChatGrpcClientPool> pool_;

};



