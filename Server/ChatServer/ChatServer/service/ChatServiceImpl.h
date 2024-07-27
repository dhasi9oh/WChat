#pragma once

#include <mutex>
#include <grpcpp/grpcpp.h>
#include <jsoncpp/json/json.h>

#include "data.h"
#include "const.h"
#include "UsrMgr.h"
#include "MysqlDao.h"
#include "RedisDao.h"
#include "message.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using message::AddFriendReq;
using message::AddFriendRsp;

using message::AuthFriendReq;
using message::AuthFriendRsp;

using message::TextChatMsgReq;
using message::TextChatMsgRsp;

using message::ChatService;


class ChatServiceImpl : public ChatService::Service
{
public:

	Status NotifyAddFriend(ServerContext* context, const AddFriendReq* request,
		AddFriendRsp* reply) override;

	Status NotifyAuthFriend(ServerContext* context,
		const AuthFriendReq* request, AuthFriendRsp* response) override;

	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UsrInfo>& userinfo);

	Status NotifyTextChatMsg(ServerContext* context, const TextChatMsgReq* request, TextChatMsgRsp* reply) override;

};