#pragma once
#include <vector>
#include "Components.h"
#include "Entity.h"

class System
{
public:
	virtual void update() = 0;
};

class HealthSystem : public System
{
	vector<Component*> components;
public:
	virtual void update();
	void add(Component* cmpt);
};

class DamageSystem : public System
{
	vector<Component*> components;
public:
	virtual void update();
	void add(Component* cmpt);
};