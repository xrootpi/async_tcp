#include "async_tcp/tcp_client.h"

tcp_client::tcp_client(char * ip_address, int port, boost::asio::io_service & io_service, message_factory * message_factory) :
m_io_service(io_service)
{
	message_factory->on_send.connect(boost::bind(&tcp_client::write_message, this, _1));
	new_connection = new connection(m_io_service);
	new_connection->message_factory = message_factory;
	connect(ip_address,port);
}

tcp_client::~tcp_client()
= default;

void tcp_client::connect(char * ip_address, int port)
{
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_address), port);

	new_connection->m_client_socket.async_connect(endpoint,
		boost::bind(&tcp_client::handle_connection, this,
		boost::asio::placeholders::error));
}

void tcp_client::handle_connection(const boost::system::error_code & err)
{
	new_connection->read();
}

void tcp_client::write_message(unsigned char * message)
{
	new_connection->write(message);
}
