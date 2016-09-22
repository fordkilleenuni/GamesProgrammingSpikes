#pragma once
#ifndef PLAYER_H
#define PLAYER_H

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

#endif // !PLAYER_H
