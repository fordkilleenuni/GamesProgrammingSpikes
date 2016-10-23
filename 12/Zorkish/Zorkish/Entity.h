#pragma once
#include <map>
#include "Component.h"
#include "Listener.h"

class Entity : public Listener
{
private:
	map<string, Component*> components;
public:
	bool addComponent(string _id, Component* _comp);
	bool removeComponent(string _identifier);
	Component* getComponent(string _identifier);
	bool hasComponent(string _identifier);
	void handleMessage(Message* _msg);
	void checkBlackboard();
};