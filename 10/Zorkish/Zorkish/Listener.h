#pragma once
#include "Message.h"

class Listener
{
public:
	virtual void handleMessage(Message* _msg) = 0;
};