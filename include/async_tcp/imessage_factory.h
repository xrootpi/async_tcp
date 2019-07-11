#pragma once
#include <boost/signals2/signal.hpp>

class imessage_factory
{
public:
	virtual void read_message(unsigned char *message, size_t connection){};
	virtual void write_message(unsigned char *message, size_t connection){};
	boost::signals2::signal<void(unsigned char*, size_t)> on_receive;
	boost::signals2::signal<void(unsigned char*, size_t)> on_send;
};

