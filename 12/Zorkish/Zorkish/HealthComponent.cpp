#include "Components.h"
#include <iostream>

const string HealthComponent::IDENTIFIER = "HLTH";

HealthComponent::HealthComponent()
{
	health = 20;
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::update()
{
	if (health <= 0)
		cout << "Entity is dead" << endl;
	else
		cout << "Entity health: " << health << endl;
}

void HealthComponent::addHealth(int _toadd)
{
	health += _toadd;
}

void HealthComponent::takeHealth(int _totake)
{
	health -= _totake;
}
