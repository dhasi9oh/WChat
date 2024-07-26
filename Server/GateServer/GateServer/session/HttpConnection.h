#pragma once

#include "const.h"
#include "LogicSystem.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:

	using TcpSocket = boost::asio::ip::tcp::socket;
	using Request = boost::beast::http::request<boost::beast::http::dynamic_body>;
	using Response = boost::beast::http::response<boost::beast::http::dynamic_body>;

	HttpConnection(boost::asio::io_context& io_context);
	~HttpConnection();

	void start();
	void httpMessageParse();
	TcpSocket& getSocket() { return m_socket; }

	Request& getRequest() { return m_request; }
	Response& getResponse() { return m_response; }

private:
	//解析报文
	void parseRequest();
	//生成http响应报文
	void makeResponse();
	//在定时器范围内发送响应报文
	void checkDeadline();

	TcpSocket m_socket;
	//接收缓冲区
	boost::beast::flat_buffer m_buffer {8192};
	//解析出来的请求报文
	Request m_request;
	//响应报文
	Response m_response;
	//请求的资源路径
	std::string m_url;
	//http的相关设置
	std::map<std::string, std::string> m_params;
	//定时器
	boost::beast::net::steady_timer m_timer;
};