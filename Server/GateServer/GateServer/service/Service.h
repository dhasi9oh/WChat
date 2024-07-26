#pragma once

#include <jsoncpp/json/json.h>

#include "const.h"
#include "MysqlDao.h"
#include "HttpConnection.h"
#include "StatusGrpcClient.h"
#include "VerifyGrpcClient.h"

using ConnPtr = std::shared_ptr<HttpConnection>;

// post接口
class PostService
{
public:

	virtual void operator()(ConnPtr) = 0;
};

class LoginService : public PostService
{
public:
	void operator()(ConnPtr) override;
};

class RegisterService : public PostService
{
public:
	void operator()(ConnPtr) override;
};

class ResetService : public PostService
{
public:
	void operator()(ConnPtr) override;
};

class GetVerifyCodeService : public PostService
{
public:
	void operator()(ConnPtr) override;
};

// get接口
class GetService
{
public:
	virtual void operator()(ConnPtr) = 0;
};