#include "Player.h"
#include "Inventory.h"

using namespace std;

Player* Player::_instance = 0;

Player::Player() {
	inventory = new Inventory();
	health = 100;
}

Player& Player::instance()
{
	if (!_instance)
	{
		_instance = new Player;
		_instance->set_name("player");
	}
	return *_instance;
}

int Player::getHealth() {
	return health;
}

Inventory* Player::getInventory() {
	return inventory;
}

void Player::action(Action _action, string _name)
{
	if (_name == "INVENTORY")
	{
		cout << "You currently have:" << endl;
		printitems();
		return;
	}
	for (map<string, Component*>::iterator i = items.begin(); i != items.end(); i++)
		i->second->action(_action, _name);
}
