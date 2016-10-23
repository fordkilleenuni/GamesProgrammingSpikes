#pragma once
#include "Listener.h"
#include <vector>
#include <map>

class Messenger
{
private:
	Messenger();
	int _currid;
	static Messenger *_instance;
	vector<Listener*> listeners;
	map<int, Message*> blackboard;
public:
	static Messenger &instance();
	void addListener(Listener* _listener);
	void sendMessage(Message* _message);
	void sendAnnouncement(Message* _message);
	void addBlackboardMessage(Message* _message);
	void removeBlackboardMessage(int _mID);
	map<int, Message*> viewBlackboard();
	int getNextId();
};