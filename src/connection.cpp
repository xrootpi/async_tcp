#include "async_tcp/connection.h"

connection::connection(boost::asio::io_service & io_service) :
	m_io_service(io_service),
	m_client_socket(io_service), m_buffer{}
{
}

connection::~connection()
= default;

boost::asio::ip::tcp::socket * connection::create_socket()
{
	return &m_client_socket;
}

void connection::read_from_client(const boost::system::error_code & error, size_t bytes_transferred, size_t connection)
{
	if(!error)
	{
		m_buffer[bytes_transferred] = 0;
		m_factory->read_message(m_buffer, connection);
		read(connection);
		m_buffer[bytes_transferred] = 0;
	} else
	{
		DEBUG_CONSOLE("connection::read_from_client: error");
		m_client_socket.close();
	}
}

void connection::read()
{
	read(NULL);
}

void connection::read(size_t connection_hash)
{
	m_client_socket.async_read_some(boost::asio::buffer(m_buffer, sizeof(m_buffer)),
		boost::bind(&connection::read_from_client, 
		this, 
		boost::asio::placeholders::error, 
		boost::asio::placeholders::bytes_transferred,
		connection_hash));
}

void connection::send_to_client(const boost::system::error_code & error, size_t bytes_transferred)
{
	if (!error)
	{
		DEBUG_CONSOLE("connection::send_to_client: Messsage Sent");
	}
	else {
		DEBUG_CONSOLE("error connection::send_to_client");
	}
}

void connection::write(unsigned char * message)
{
	m_client_socket.async_write_some(boost::asio::buffer(message, std::strlen(reinterpret_cast<char*>(message))), 
		boost::bind(&connection::send_to_client,
		this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void connection::close()
{
	m_client_socket.close();
}
