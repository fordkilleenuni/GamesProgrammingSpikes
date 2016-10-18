#pragma once
#include "Inventory.h"
#include "Component.h"

using namespace std;

class Player : public Container {
public:
	static Player &instance();
	int getHealth();
	Inventory* getInventory();
	void action(Action _action, string _name);
private:
	Player();
	static Player *_instance;
	int health;
	Inventory* inventory;
};
