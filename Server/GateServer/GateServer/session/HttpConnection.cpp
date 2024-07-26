#include "HttpConnection.h"

//���ַ�ת��Ϊ16����
unsigned char ToHex(char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

//16����תΪһ���ֽڵ�����
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
		//�ж��Ƿ�������ֺ���ĸ����
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ') //Ϊ���ַ�
			strTemp += "+";
		else
		{
			//�����ַ���Ҫ��ǰ��%���Ҹ���λ�͵���λ�ֱ�תΪ16����
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
		//��ԭ+Ϊ��
		if (str[i] == '+') strTemp += ' ';
		//����%������������ַ���16����תΪchar��ƴ��
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

				// ���������Ĳ�������Ӧ����
				self->httpMessageParse();
				// ����涨ʱ����Ϊ��������Ӧ������ر�����
				self->checkDeadline();
			}
			catch (const std::exception& e) {
				LOG_WARN("HttpConnection::start() exception: {}", e.what());
			}
		});
}

void HttpConnection::httpMessageParse()
{
	//�������ɵ���Ӧ���ĵİ汾
	m_response.version(m_request.version());
	//���ö�����
	m_response.keep_alive(false);

	if (m_request.method() == boost::beast::http::verb::post) {
		//����������
		parseRequest();
		
		//��������
		auto self = shared_from_this();
		bool success = LogicSystem::Instance()->handlePost(m_url, self);

		//û���ҵ���Ӧ����Դ
		if (!success) {
			m_response.result(boost::beast::http::status::not_found);
			m_response.set(boost::beast::http::field::content_type, "text/plain");
			boost::beast::ostream(m_response.body()) << "Not found";
			makeResponse();
			return;
		}

		//�ɹ�
		m_response.result(boost::beast::http::status::ok);
		m_response.set(boost::beast::http::field::server, "GateServer");
		boost::beast::ostream(m_response.body()) << "Success";
		makeResponse();
		return;
	}

	if (m_request.method() == boost::beast::http::verb::get) {
		//��������
		auto self = shared_from_this();
		bool success = LogicSystem::Instance()->handleGet(m_url, self);

		if (!success) {
			m_response.result(boost::beast::http::status::not_found);
			m_response.set(boost::beast::http::field::content_type, "text/plain");
			boost::beast::ostream(m_response.body()) << "Not found";
			makeResponse();
			return;
		}

		//�ɹ�
		m_response.result(boost::beast::http::status::ok);
		m_response.set(boost::beast::http::field::server, "GateServer");
		boost::beast::ostream(m_response.body()) << "Success";
		makeResponse();
		return;
	}
}

void HttpConnection::parseRequest()
{
	//��ȡ�����uri
	auto uri = m_request.target();
	int pos = uri.find('?');
	//��ѯ�ַ����Ŀ�ʼλ��
	if (pos == std::string::npos) {
		m_url = uri.to_string();
		return;
	}

	m_url = uri.substr(0, pos).to_string();
	//��ȡ�����к���ַ���
	std::string query_string = uri.substr(pos + 1).to_string();
	std::string key, value;
	size_t idx = 0;
	//����&��˵������key=value�ļ�ֵ��
	while ((idx = query_string.find('&')) != std::string::npos) {
		//��ȡkey=value��ֵ��
		auto pair = query_string.substr(0, idx);
		//�ҵ�=��λ��
		size_t key_pos = pair.find('=');
		if (pos == std::string::npos) {
			//��ȡkey������
			key = UrlDecode(pair.substr(0, key_pos));
			//��ȡvalue������
			value = UrlDecode(pair.substr(key_pos + 1));
			m_params[key] = value;
		}
		//��ȡ��һ����ֵ��
		query_string = query_string.substr(idx + 1);
	}

	//���һ����ֵ��
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

	// ������Ӧ����
	boost::beast::http::async_write(m_socket, m_response,
		[self](boost::beast::error_code ec, std::size_t bytes_transferred) {
			// ����
			if (ec) {
				LOG_WARN("HttpConnection::makeResponse() write error: {}", ec.message());
				return;
			}
			// �ر�����
			// ʹ��shutdown�رշ��ͷ�������ӣ�������շ�������ӱ��ر�
			self->m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
			self->m_timer.cancel();
		}
	);
}

void HttpConnection::checkDeadline()
{
	auto self(shared_from_this());
	//����ʱ����ʱʱ�ر����Ӳ������־
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
