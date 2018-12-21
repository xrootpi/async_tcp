#pragma once
#include <boost/asio.hpp>
#include "message_factory.h"

class connection
{
public:
	explicit connection(boost::asio::io_service& io_service);
	virtual ~connection();
	boost::asio::ip::tcp::socket m_client_socket;
	boost::asio::ip::tcp::socket* create_socket();
	void read_from_client(const boost::system::error_code& error, size_t bytes_transferred);
	void read();
	void send_to_client(const boost::system::error_code& error, size_t bytes_transferred);
	void write(unsigned char *message);
	unsigned char m_buffer[1024];
	boost::asio::io_service& m_io_service;
	message_factory *message_factory;
	void close();
};