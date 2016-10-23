#pragma once
#include <iostream>

using namespace std;

enum Tag { ALL, HEALTH, DAMAGE };

class Message
{
private:
	int id;
	Tag tag;
	string content;
public:
	Message(Tag _tag, string _content);
	void Message::setId(int _id);
	int getId();
	Tag getTag();
	string getContents();
};