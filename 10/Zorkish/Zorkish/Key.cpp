#include "GameItems.h"

Key::Key()
{
	name = "Key";
	description = "A small golden key";
	quantity = 1;
}

Key::~Key()
{
	// ?
}

int Key::getID()
{
	return InventoryItem::KEY;
}

string Key::getName()
{
	return name;
}

string Key::getDescription()
{
	return description;
}

int Key::getQuantity()
{
	return quantity;
}

bool Key::increaseQuantity(int amount)
{
	quantity += amount;
	return true;
}

void Key::use()
{
	cout << "You use your key and unlock the door " << endl;
}