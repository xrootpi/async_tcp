#pragma once
#include <boost/asio/io_service.hpp>
#include "message_factory.h"
#include "connection.h"

class tcp_client
{
public:
	tcp_client(char *ip_address, int port, boost::asio::io_service& io_service, message_factory* message_factory);
	virtual ~tcp_client();
	boost::asio::io_service& m_io_service;
	connection *new_connection;
	void connect(char *ip_address, int port);
	void handle_connection(const boost::system::error_code& err);
	void write_message(unsigned char *message);
};

