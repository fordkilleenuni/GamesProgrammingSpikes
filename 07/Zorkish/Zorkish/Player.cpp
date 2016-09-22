#include "Player.h"
#include "Inventory.h"

using namespace std;

Player::Player() {
	inventory = new Inventory();
	health = 100;
}

Player::~Player() {
	delete inventory;
}

int Player::getHealth() {
	return health;
}

Inventory* Player::getInventory() {
	return inventory;
}