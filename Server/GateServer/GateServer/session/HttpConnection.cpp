#include "HttpConnection.h"

//将字符转化为16进制
unsigned char ToHex(char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

//16进制转为一个字节的整数
unsigned char FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}

std::string UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		//判断是否仅有数字和字母构成
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ') //为空字符
			strTemp += "+";
		else
		{
			//其他字符需要提前加%并且高四位和低四位分别转为16进制
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] & 0x0F);
		}
	}
	return strTemp;
}

std::string UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		//还原+为空
		if (str[i] == '+') strTemp += ' ';
		//遇到%将后面的两个字符从16进制转为char再拼接
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}

HttpConnection::HttpConnection(boost::asio::io_context& io_context)
	: m_socket(io_context)
	, m_timer(io_context, std::chrono::seconds(60))
{
}

HttpConnection::~HttpConnection()
{
}

void HttpConnection::start()
{
	auto self(shared_from_this());
	boost::beast::http::async_read(m_socket, m_buffer, m_request,
		[self](boost::beast::error_code ec, std::size_t bytes_transferred) {
			try {
				if (ec) {
					LOG_WARN("HttpConnection::start() read error: {}", ec.message());
					return;
				}

				// 解析请求报文并生成响应报文
				self->httpMessageParse();
				// 如果规定时间内为发送完响应报文则关闭连接
				self->checkDeadline();
			}
			catch (const std::exception& e) {
				LOG_WARN("HttpConnection::start() exception: {}", e.what());
			}
		});
}

void HttpConnection::httpMessageParse()
{
	//设置生成的响应报文的版本
	m_response.version(m_request.version());
	//设置短连接
	m_response.keep_alive(false);

	if (m_request.method() == boost::beast::http::verb::post) {
		//解析请求报文
		parseRequest();
		
		//处理请求
		auto self = shared_from_this();
		bool success = LogicSystem::Instance()->handlePost(m_url, self);

		//没有找到对应的资源
		if (!success) {
			m_response.result(boost::beast::http::status::not_found);
			m_response.set(boost::beast::http::field::content_type, "text/plain");
			boost::beast::ostream(m_response.body()) << "Not found";
			makeResponse();
			return;
		}

		//成功
		m_response.result(boost::beast::http::status::ok);
		m_response.set(boost::beast::http::field::server, "GateServer");
		boost::beast::ostream(m_response.body()) << "Success";
		makeResponse();
		return;
	}

	if (m_request.method() == boost::beast::http::verb::get) {
		//处理请求
		auto self = shared_from_this();
		bool success = LogicSystem::Instance()->handleGet(m_url, self);

		if (!success) {
			m_response.result(boost::beast::http::status::not_found);
			m_response.set(boost::beast::http::field::content_type, "text/plain");
			boost::beast::ostream(m_response.body()) << "Not found";
			makeResponse();
			return;
		}

		//成功
		m_response.result(boost::beast::http::status::ok);
		m_response.set(boost::beast::http::field::server, "GateServer");
		boost::beast::ostream(m_response.body()) << "Success";
		makeResponse();
		return;
	}
}

void HttpConnection::parseRequest()
{
	//获取请求的uri
	auto uri = m_request.target();
	int pos = uri.find('?');
	//查询字符串的开始位置
	if (pos == std::string::npos) {
		m_url = uri.to_string();
		return;
	}

	m_url = uri.substr(0, pos).to_string();
	//截取请求行后的字符串
	std::string query_string = uri.substr(pos + 1).to_string();
	std::string key, value;
	size_t idx = 0;
	//存在&则说明还有key=value的键值对
	while ((idx = query_string.find('&')) != std::string::npos) {
		//截取key=value键值对
		auto pair = query_string.substr(0, idx);
		//找到=的位置
		size_t key_pos = pair.find('=');
		if (pos == std::string::npos) {
			//截取key并解码
			key = UrlDecode(pair.substr(0, key_pos));
			//截取value并解码
			value = UrlDecode(pair.substr(key_pos + 1));
			m_params[key] = value;
		}
		//截取下一个键值对
		query_string = query_string.substr(idx + 1);
	}

	//最后一个键值对
	if (!query_string.empty()) {
		size_t key_pos = query_string.find('=');
		if (pos == std::string::npos) {
			key = UrlDecode(query_string.substr(0, key_pos));
			value = UrlDecode(query_string.substr(key_pos + 1));
			m_params[key] = value;
		}
	}
}

void HttpConnection::makeResponse()
{
	auto self(shared_from_this());

	// 发送响应报文
	boost::beast::http::async_write(m_socket, m_response,
		[self](boost::beast::error_code ec, std::size_t bytes_transferred) {
			// 报错
			if (ec) {
				LOG_WARN("HttpConnection::makeResponse() write error: {}", ec.message());
				return;
			}
			// 关闭连接
			// 使用shutdown关闭发送方向的连接，避免接收方向的连接被关闭
			self->m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
			self->m_timer.cancel();
		}
	);
}

void HttpConnection::checkDeadline()
{
	auto self(shared_from_this());
	//当定时器超时时关闭连接并输出日志
	m_timer.async_wait(
		[self] (const boost::system::error_code& ec)
		{
			if (!ec) {
				LOG_WARN("HttpConnection::checkDeadline() timeout {}",
					self->getSocket().local_endpoint().address().to_string());
				self->m_socket.close();
			}
		});
}
