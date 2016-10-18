#pragma once
#include "Component.h"

class Sword : public Item
{
public:
	Sword();
	void action(Action _action, string _name);
};

class Bread : public Item
{
public:
	Bread();
	void action(Action _action, string _name);
};