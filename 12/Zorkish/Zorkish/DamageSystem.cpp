#include "System.h"

void DamageSystem::update()
{
	for each (Component* component in components)
	{
		component->update();
	}
}

void DamageSystem::add(Component* cmpt)
{
	components.push_back(cmpt);
}