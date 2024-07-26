#include "StatusGrpcClient.h"

GetChatServerRsp StatusGrpcClient::getChatServer(int uid)
{
	ClientContext context;
	//grpc生成的请求报文类型
	GetChatServerReq req;
	//grpc生成的响应报文类型
	GetChatServerRsp rsp;
	//设置请求报文中的相关字段
	req.set_uid(uid);
	auto stub = m_conPool->getStub();
	Status status = stub->GetChatServer(&context, req, &rsp);

	Defer defer([this, &stub] { m_conPool->releaseStub(std::move(stub)); });

	if (status.ok()) {
		return rsp;
	}

	rsp.set_error(ErrorCodes::RPCFailed);
	return rsp;
}

LoginRsp StatusGrpcClient::login(int uid, const std::string& token)
{
	ClientContext context;
	//grpc生成的登录请求报文
	LoginReq req;
	//grpc生成的登录响应报文
	LoginRsp rsp;
	//设置请求报文中的相关字段
	req.set_uid(uid);
	req.set_token(token);
	
	auto stub = m_conPool->getStub();
	Status status = stub->Login(&context, req, &rsp);

	Defer defer([this, &stub] { m_conPool->releaseStub(std::move(stub)); });

	if (status.ok()) {
		return rsp;
	}

	rsp.set_error(ErrorCodes::RPCFailed);
	return rsp;
}

StatusGrpcClient::StatusGrpcClient()
{
	auto& gCfgMgr = ConfigMgr::Instance();
	std::string host = gCfgMgr["StatusServer"]["Host"];
	std::string port = gCfgMgr["StatusServer"]["Port"];
	m_conPool.reset(new StatusConPool(5, host, port));
}