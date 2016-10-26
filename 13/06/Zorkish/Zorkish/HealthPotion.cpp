#include "GameItems.h"

HealthPotion::HealthPotion()
{
	name = "Health Potion";
	description = "A small health potion for regaining health";
	quantity = 1;
	healthToRestore = 5;
}

HealthPotion::~HealthPotion()
{
	// ?
}

int HealthPotion::getID() const
{
	return InventoryItem::HEALTHPOTION;
}

string HealthPotion::getName() const
{
	return name;
}

string HealthPotion::getDescription() const
{
	return description;
}

int HealthPotion::getQuantity()
{
	return quantity;
}

bool HealthPotion::increaseQuantity(int amount)
{
	quantity += amount;
	return true;
}

void HealthPotion::use()
{
	cout << "You use your health potion and regain " << healthToRestore << " health!" << endl;
	quantity -= 1;
}