#pragma once

#include "Inventory.h"

using namespace std;

class Player {
public:
	Player();
	~Player();
	int getHealth();
	Inventory* getInventory();
private:
	int health;
	Inventory* inventory;
};
