#include "MsgNode.h"


SendMsgNode::SendMsgNode(const char* ptr, size_t size, short msg_id)
	: MsgNode(size + HEAD_TOTAL_LEN)
	, m_msg_id(msg_id)
{
	short id = boost::asio::detail::socket_ops::host_to_network_short(msg_id);
	memcpy(m_ptr, &id, HEAD_ID_LEN);

	short len = boost::asio::detail::socket_ops::host_to_network_short(size);
	memcpy(m_ptr + HEAD_ID_LEN, &len, HEAD_DATA_LEN);

	memcpy(m_ptr + HEAD_TOTAL_LEN, ptr, size);
}
