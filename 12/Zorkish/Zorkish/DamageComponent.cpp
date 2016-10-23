#include "Components.h"
#include <iostream>

const string DamageComponent::IDENTIFIER = "DMG";

DamageComponent::DamageComponent()
{
	damageToDeal = 0;
}

DamageComponent::~DamageComponent()
{
}

void DamageComponent::update()
{
	damageToDeal = 0;
}

void DamageComponent::setDamage(int _damage)
{
	damageToDeal += _damage;
}
