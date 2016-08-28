#pragma once
#ifndef BASESTATE_H
#define BASESTATE_H
#include "StateManager.h"

class BaseState
{
public:
	virtual void handleInput() {};
	virtual void update(StateManager &manager) {};
	virtual void drawState() {};
};

#endif // !BASESTATE_H