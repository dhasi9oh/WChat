#pragma once

#include <map>
#include <grpcpp/grpcpp.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "const.h"
#include "ConfigMgr.h"
#include "message.pb.h"
#include "message.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

struct ChatServer
{
	std::string host;
	std::string port;
	std::string name;
	int con_count;
};


class StatusServiceImpl final : public StatusService::Service
{
public:

	StatusServiceImpl();

	Status Login(ServerContext* context, const LoginReq* request, LoginRsp* response) override;

	Status GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* response) override;

private:

	void insertToken(int uid, std::string token);

	void removeToken(int uid);

	ChatServer getChatServer();

	std::mutex m_tokenMutex;
	std::mutex m_serverMutex;
	std::map<int, std::string> m_tokens;
	std::map<std::string, ChatServer> m_chatServers;

};