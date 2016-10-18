#pragma once
#include "StateManager.h"

class BaseState
{
public:
	virtual void handleInput() {};
	virtual void update(StateManager &manager) {};
	virtual void drawState() {};
};