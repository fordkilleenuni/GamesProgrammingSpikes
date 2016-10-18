#include "System.h"

void HealthSystem::update()
{
	for each (Component* component in components)
	{
		component->update();
	}
}

void HealthSystem::add(Component* cmpt)
{
	components.push_back(cmpt);
}