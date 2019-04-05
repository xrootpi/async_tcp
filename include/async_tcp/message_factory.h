#pragma once
#include <boost/signals2.hpp>
#include "debug_output.h"

class message_factory
{
public:
	message_factory();
	virtual ~message_factory();
	void read_message(unsigned char *message, size_t connection);
	void write_message(unsigned char *message, size_t connection);
	boost::signals2::signal<void(unsigned char*, size_t)> on_receive;
	boost::signals2::signal<void(unsigned char*, size_t)> on_send;
};