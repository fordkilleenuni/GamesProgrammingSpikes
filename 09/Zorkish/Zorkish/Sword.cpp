#include "GameItems.h"

ASword::ASword()
{
	name = "Sword";
	description = "A basic steel sword with a worn leather handle";
	quantity = 1;
	damage = 10;
}

ASword::~ASword()
{
	// ?
}

int ASword::getID()
{
	return InventoryItem::SWORD;
}

string ASword::getName()
{
	return name;
}

string ASword::getDescription()
{
	return description;
}

int ASword::getQuantity()
{
	return quantity;
}

bool ASword::increaseQuantity(int amount)
{
	quantity += amount;
	return true;
}

void ASword::use()
{
	cout << "You use your basic sword and deal " << damage << " damage!" << endl;
}