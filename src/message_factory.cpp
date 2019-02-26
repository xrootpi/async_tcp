#include "async_tcp/message_factory.h"
#include "async_tcp/debug_output.h"

message_factory::message_factory()
= default;

message_factory::~message_factory()
= default;

void message_factory::read_message(unsigned char * message)
{
	on_receive(message);
}

void message_factory::write_message(unsigned char * message)
{
	on_send(message);
}
