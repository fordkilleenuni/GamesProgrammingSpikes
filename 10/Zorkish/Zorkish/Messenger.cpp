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
	for each (Listener* listener in listeners)
	{
		listener->handleMessage(_message);
	}
}

int Messenger::getNextId()
{
	return _currid++;
}
