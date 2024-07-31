#include "TcpConnection.h"

TcpClient::TcpClient(boost::asio::io_context& io_context, ChatServer* server)
	: m_socket(io_context)
	, m_server(server)
	, b_stop(false)
	, b_headerParse(false)
	, m_uid(0)
{
	//����sessionID
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	m_sessionID = boost::uuids::to_string(uuid);
	m_recvHeaderNode = std::make_shared<MsgNode>(HEAD_TOTAL_LEN);
}

TcpClient::~TcpClient()
{
	LOG_INFO("uid: {} is close", m_uid);
}

std::string& TcpClient::sessionID()
{
	return m_sessionID;
}

boost::asio::ip::tcp::socket& TcpClient::socket()
{
	return m_socket;
}

void TcpClient::setUserID(int uid)
{
	m_uid = uid;
}

int TcpClient::getUserID() const
{
	return m_uid;
}

void TcpClient::start()
{
	asyncReadHeader(HEAD_TOTAL_LEN);
}

void TcpClient::close()
{
	b_stop = true;
	m_socket.close();
}

void TcpClient::send(const std::string& message, int msg_id)
{
	send(message.c_str(), message.length(), msg_id);
}

void TcpClient::send(const char* message, int length, int msg_id)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	int send_que_size = m_sendMsgQueue.size();
	if (send_que_size > MAX_SEND_QUEUE_SIZE) {
		LOG_WARN("uid: {} send queue full, size is {}", m_uid, send_que_size);
		return;
	}

	m_sendMsgQueue.push(std::make_shared<SendMsgNode>(message, length, msg_id));
	//sendһ�λ�ѷ��Ͷ�����գ��������ԭ������0��˵���������ڷ��ͣ����ٷ���
	if (send_que_size > 0) return;

	auto &send_msg_node = m_sendMsgQueue.front();
	boost::asio::async_write(m_socket, boost::asio::buffer(send_msg_node->data_ptr, send_msg_node->size),
		std::bind(&TcpClient::handleWrite, this, std::placeholders::_1, sharedSelf()));
}

std::shared_ptr<TcpClient> TcpClient::sharedSelf()
{
	return shared_from_this();
}

void TcpClient::asyncReadBody(int len)
{
	auto self = shared_from_this();
	asyncReadFull(len, 
		[self, this, len](const boost::system::error_code& ec, size_t bytes_transferred)
		{
			if (ec) {
				LOG_WARN("uid: {} handle read failed, error is {}", m_uid, ec.message());
				m_server->clearSession(m_sessionID);
				close();
				return;
			}

			if (bytes_transferred < len) {
				LOG_WARN("uid: {} read length not match, read [{}] , total [{}]", m_uid, bytes_transferred, len);
				m_server->clearSession(m_sessionID);
				close();
				return;
			}

			memcpy(m_recvMsgNode->data_ptr, m_buf, bytes_transferred);
			m_recvMsgNode->total += bytes_transferred;
			m_recvMsgNode->data_ptr[m_recvMsgNode->size] = '\0';

			//������Ϣ�������ҵ��
			LogicSystem::Instance()->postMsgToQue(std::make_shared<LogicNode>(shared_from_this(), m_recvMsgNode));

			//����������Ϣ
			asyncReadHeader(HEAD_TOTAL_LEN);
		});
}

void TcpClient::asyncReadHeader(int len)
{
	auto self = shared_from_this();
	asyncReadFull(HEAD_TOTAL_LEN,
		[self, this](const boost::system::error_code& ec, size_t bytes_transferred)
		{
			try {
				//���ִ���
				if (ec) {
					LOG_WARN("uid: {} asyncReadHeader error: {}", m_uid, ec.message());
					m_server->clearSession(m_sessionID);
					close();
					return;
				}

				//û������ô���ֽ�
				if (bytes_transferred < HEAD_TOTAL_LEN) {
					LOG_WARN("uid: {} asyncReadHeader error: read head failed", m_uid);
					m_server->clearSession(m_sessionID);
					close();
					return;
				}

				//�������ͷ���Ļ�����
				m_recvHeaderNode->clear();
				//�����յ�ͷ�����ݷ���û�����
				memcpy(m_recvHeaderNode->data_ptr, m_buf, HEAD_TOTAL_LEN);
				//ȡ��Ϣid
				short msg_id = 0;
				memcpy(&msg_id, m_recvHeaderNode->data_ptr, HEAD_ID_LEN);
				//�ֽ����ת��
				msg_id = boost::asio::detail::socket_ops::network_to_host_short(msg_id);
				//id�Ƿ�
				if (msg_id > MAX_LENGTH) {
					LOG_WARN("uid: {} invalid msg_id is {}", m_uid, msg_id);
					m_server->clearSession(m_sessionID);
					return;
				}

				//ȡ��Ϣ����
				short msg_len = 0;
				memcpy(&msg_len, m_recvHeaderNode->data_ptr + HEAD_ID_LEN, HEAD_DATA_LEN);
				//�ֽ����ת��
				msg_len = boost::asio::detail::socket_ops::network_to_host_short(msg_len);
				//��Ϣ���ȷǷ�
				if (msg_len > MAX_LENGTH) {
					LOG_WARN("uid: {} invalid data length is {}", m_uid, msg_id);
					m_server->clearSession(m_sessionID);
					return;
				}

				m_recvMsgNode = std::make_shared<RecvMsgNode>(msg_len, msg_id);
				asyncReadBody(msg_len);
			}
			catch (const std::exception& e) {
				LOG_WARN("uid: {} asyncReadHeader exception: {}", m_uid, e.what());
			}
		});
}

void TcpClient::asyncReadFull(int len, std::function<void(const boost::system::error_code&, size_t)> handler)
{
	//��������
	::memset(m_buf, 0, len);
	asyncReadLength(0, len, handler);
}

void TcpClient::asyncReadLength(int read_len, int total_len, std::function<void(const boost::system::error_code&, size_t)> handler)
{
	auto self = shared_from_this();
	m_socket.async_read_some(boost::asio::buffer(m_buf + read_len, total_len - read_len),
		[read_len, total_len, handler, self](const	boost::system::error_code& ec, size_t bytes_transferred)
		{
			//���ִ���
			if (ec) {
				handler(ec, read_len + bytes_transferred);
				return;
			}

			//���ȹ��˾͵��ûص�����
			if (read_len + bytes_transferred >= total_len) {
				handler(ec, read_len + bytes_transferred);
				return;
			}

			//���Ȳ����ͼ�����
			self->asyncReadLength(read_len + bytes_transferred, total_len, handler);
		});
}

void TcpClient::handleWrite(const boost::system::error_code& ec, std::shared_ptr<TcpClient> shared_self)
{
	try {
		//����͹ر�����
		if (ec) {
			LOG_WARN("uid: {} handleWrite error: {}", m_uid, ec.message());
			m_server->clearSession(m_sessionID);
			close();
			return;
		}

		std::lock_guard<std::mutex> lock(m_mutex);
		//������ϣ��Ӷ�����ɾ��
		m_sendMsgQueue.pop();

		//������������ڶ����У��ͼ�������
		if (!m_sendMsgQueue.empty()) {
			auto& send_msg_node = m_sendMsgQueue.front();
			boost::asio::async_write(m_socket, boost::asio::buffer(send_msg_node->data_ptr, send_msg_node->total),
				std::bind(&TcpClient::handleWrite, this, std::placeholders::_1, shared_self));
		}
	}
	catch (const std::exception& e) {
		LOG_WARN("uid: {} handleWrite exception: {}", m_uid, e.what());
	}
}

LogicNode::LogicNode(std::shared_ptr<TcpClient> session, std::shared_ptr<RecvMsgNode> node)
	: m_session(session)
	, m_recvNode(node)
{
}
