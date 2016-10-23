#include "Messenger.h"

Messenger* Messenger::_instance = 0;

Messenger::Messenger()
{
	_currid = 0;
}

Messenger& Messenger::instance()
{
	if (!_instance)
		_instance = new Messenger;
	return *_instance;
}

void Messenger::addListener(Listener * _listener)
{
	listeners.push_back(_listener);
}

void Messenger::sendMessage(Message * _message)
{
	_message->setId(getNextId());
	for each (Listener* listener in listeners)
	{
		listener->handleMessage(_message);
	}
}

void Messenger::sendAnnouncement(Message * _message)
{
	_message->setId(getNextId());
	for each (Listener* listener in listeners)
	{
		listener->handleMessage(_message);
	}
}

void Messenger::addBlackboardMessage(Message * _message)
{
	_message->setId(getNextId());
	blackboard[_currid] = _message;
}

void Messenger::removeBlackboardMessage(int _mID)
{
	blackboard.erase(_mID);
}

map<int, Message*> Messenger::viewBlackboard()
{
	return blackboard;
}

int Messenger::getNextId()
{
	return _currid++;
}
