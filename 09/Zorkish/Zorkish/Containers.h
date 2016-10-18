#pragma once
#include "Component.h"

class Chest : public Container
{
public:
	Chest();
	Chest(bool _locked, bool _open);
	void action(Action _action, string _name);
};