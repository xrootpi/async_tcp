#pragma once
#include <boost/signals2.hpp>

class message_factory
{
public:
	message_factory();
	virtual ~message_factory();
	void read_message(unsigned char *message);
	void write_message(unsigned char *message);
	boost::signals2::signal<void(unsigned char*)> on_receive;
	boost::signals2::signal<void(unsigned char*)> on_send;
};