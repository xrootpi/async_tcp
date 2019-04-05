#include "async_tcp/message_factory.h"
#include "async_tcp/debug_output.h"

message_factory::message_factory()
= default;

message_factory::~message_factory()
= default;

void message_factory::read_message(unsigned char * message, size_t connection)
{
	on_receive(message, connection);
}

void message_factory::write_message(unsigned char * message, size_t connection)
{
	on_send(message, connection);
}
