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
	//��������
	void parseRequest();
	//����http��Ӧ����
	void makeResponse();
	//�ڶ�ʱ����Χ�ڷ�����Ӧ����
	void checkDeadline();

	TcpSocket m_socket;
	//���ջ�����
	boost::beast::flat_buffer m_buffer {8192};
	//����������������
	Request m_request;
	//��Ӧ����
	Response m_response;
	//�������Դ·��
	std::string m_url;
	//http���������
	std::map<std::string, std::string> m_params;
	//��ʱ��
	boost::beast::net::steady_timer m_timer;
};