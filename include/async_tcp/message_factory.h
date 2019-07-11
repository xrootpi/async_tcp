#pragma once
#include <boost/signals2.hpp>
#include "debug_output.h"
#include "imessage_factory.h"

class message_factory: public imessage_factory
{
public:
	message_factory();
	virtual ~message_factory();
	void read_message(unsigned char * message, size_t connection) override;
	void write_message(unsigned char * message, size_t connection) override;
};
