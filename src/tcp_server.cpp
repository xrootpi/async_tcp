#include "async_tcp/tcp_server.h"

tcp_server::tcp_server(char * ip_address, const int port, boost::asio::io_service & io_service, message_factory * message_factory):
	m_io_service(io_service),
	m_client_acceptor(io_service),
	_message_factory(message_factory)
{
	DEBUG_CONSOLE("starting tcp_server");
	_message_factory->on_receive.connect(boost::bind(&tcp_server::broadcast, this, _1));
	tcp_server::initiate_acceptor(ip_address, port);
}

tcp_server::~tcp_server()
= default;

void tcp_server::initiate_acceptor(char * ip_address, int port)
{
	const auto listen_address = boost::asio::ip::address_v4::from_string(ip_address);
	boost::asio::ip::tcp::endpoint endpoint(listen_address,static_cast<unsigned short>(port));
	m_client_acceptor.open(endpoint.protocol());
	m_client_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_client_acceptor.bind(endpoint);
	m_client_acceptor.listen();
	DEBUG_CONSOLE("Connection initiated");
	start_accept();
}

void tcp_server::start_accept()
{
	try
	{
		auto *new_connection = new connection(m_io_service);
		auto handle = new_connection;
		handle->message_factory = _message_factory;

		m_client_acceptor.async_accept(handle->m_client_socket,
			boost::bind(&tcp_server::on_socket_accept, this, boost::asio::placeholders::error, handle));

		new_connection->close();
	}
	catch (boost::system::system_error& e)
	{
		DEBUG_CONSOLE("tcp_server::start_accept: error");
	}
}

void tcp_server::on_socket_accept(const boost::system::error_code & error, connection * handle)
{
	try
	{
		DEBUG_CONSOLE("Connection accepted");
		const std::hash<connection*> hash_fn;
		const auto hash = hash_fn(handle);
		connections[hash] = handle;
		handle->read();
		start_accept();
	}
	catch (boost::system::system_error& e)
	{
		DEBUG_CONSOLE("tcp_server::on_socket_accept: error");
	}
}
void tcp_server::run() const
{
	DEBUG_CONSOLE("starting up service");
	m_io_service.run();
}

void tcp_server::broadcast(unsigned char * message)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
	{
		auto *handle = static_cast<connection*>(it->second);
		handle->write(message);
	}
}