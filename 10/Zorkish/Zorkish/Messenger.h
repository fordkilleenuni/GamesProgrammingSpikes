#pragma once
#include "Listener.h"
#include <vector>

class Messenger
{
private:
	Messenger();
	int _currid;
	static Messenger *_instance;
	vector<Listener*> listeners;
public:
	static Messenger &instance();
	void addListener(Listener *_listener);
	void sendMessage(Message *_message);
	int getNextId();
};