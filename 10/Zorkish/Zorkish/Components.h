#pragma once
#include "Component.h"

class HealthComponent : public Component
{
private:
	int health;
public:
	HealthComponent();
	~HealthComponent();
	virtual void update();
	static const string IDENTIFIER;
	void addHealth(int _toadd);
	void takeHealth(int _totake);
};

class DamageComponent : public Component
{
private:
	int damageToDeal;
public:
	DamageComponent();
	~DamageComponent();
	virtual void update();
	static const string IDENTIFIER;
	void setDamage(int _damage);
};

class DamageableComponent : public Component
{
public:
	DamageableComponent();
	~DamageableComponent();
	virtual void update();
	static const string IDENTIFIER;
};

class PickupableComponent : public Component
{
public:
	PickupableComponent();
	~PickupableComponent();
	virtual void update();
	static const string IDENTIFIER;
};