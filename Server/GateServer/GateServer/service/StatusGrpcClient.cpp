#include "StatusGrpcClient.h"

GetChatServerRsp StatusGrpcClient::getChatServer(int uid)
{
	ClientContext context;
	//grpc���ɵ�����������
	GetChatServerReq req;
	//grpc���ɵ���Ӧ��������
	GetChatServerRsp rsp;
	//�����������е�����ֶ�
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
	//grpc���ɵĵ�¼������
	LoginReq req;
	//grpc���ɵĵ�¼��Ӧ����
	LoginRsp rsp;
	//�����������е�����ֶ�
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