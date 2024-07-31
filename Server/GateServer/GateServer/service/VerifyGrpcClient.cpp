#include "VerifyGrpcClient.h"

VericfyGrpcClientt::VericfyGrpcClientt()
{
	auto& gCfgMgr = ConfigMgr::Instance();
	std::string host = gCfgMgr["VarifyServer"]["host"];
	std::string port = gCfgMgr["VarifyServer"]["port"];
	m_conPool.reset(new VericfyConPool(5, host, port));
}

GetVarifyRsp VericfyGrpcClientt::GetVarifyCode(std::string email)
{
	ClientContext context;
	//grpc���ɵĻ�ȡ��֤����Ӧ����
	GetVarifyRsp rsp;
	//grpc���ɵĻ�ȡ��֤��������
	GetVarifyReq req;

	req.set_email(email);
	auto conn_ptr = m_conPool->getStub();
	Defer defer([this, &conn_ptr] { m_conPool->releaseStub(std::move(conn_ptr)); });
	//grpc���û�ȡ��֤��ӿ�
	Status status = conn_ptr->GetVarifyCode(&context, req, &rsp);

	if (status.ok()) {
		return rsp;
	}

	rsp.set_error(ErrorCodes::RPCFailed);
	return rsp;
}
