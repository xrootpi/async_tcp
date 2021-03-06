#pragma once
#include <unordered_map>
#include <boost/asio/io_service.hpp>
#include "message_factory.h"
#include "connection.h"

class tcp_server
{
public:
	tcp_server(const char *ip_address, int port, boost::asio::io_service& io_service, message_factory* m_factory);
	virtual ~tcp_server();
	void initiate_acceptor(const char *ip_address, int port);
	void start_accept();
	void on_socket_accept(const boost::system::error_code& error, connection *handle);
	void run() const;
	std::hash<connection*> connection_hash;
	std::unordered_map<size_t, connection* >connections;
	void broadcast(unsigned char* message);
	void handle_send(unsigned char* message, size_t connection);
	boost::asio::ip::tcp::acceptor m_client_acceptor;
	boost::asio::io_service& m_io_service;
private:
	message_factory* _message_factory;
};

