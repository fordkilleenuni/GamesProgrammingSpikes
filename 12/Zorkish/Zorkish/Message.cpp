#include "Message.h"

Message::Message(Tag _tag, string _content)
{
	id = 0;
	tag = _tag;
	content = _content;
}

void Message::setId(int _id)
{
	id = _id;
}

int Message::getId()
{
	return id;
}

Tag Message::getTag()
{
	return tag;
}

string Message::getContents()
{
	return content;
}
