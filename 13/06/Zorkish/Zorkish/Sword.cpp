#include "GameItems.h"

Sword::Sword()
{
	name = "Sword";
	description = "A basic steel sword with a worn leather handle";
	quantity = 1;
	damage = 10;
}

Sword::~Sword()
{
	// ?
}

int Sword::getID() const
{
	return InventoryItem::SWORD;
}

string Sword::getName() const
{
	return name;
}

string Sword::getDescription() const
{
	return description;
}

int Sword::getQuantity()
{
	return quantity;
}

bool Sword::increaseQuantity(int amount)
{
	quantity += amount;
	return true;
}

void Sword::use()
{
	cout << "You use your basic sword and deal " << damage << " damage!" << endl;
}