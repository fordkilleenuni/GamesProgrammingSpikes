#include <stdio.h>
#include <iostream>
#include "Inventory.h"

using namespace std;

Inventory::Inventory()
{
	maxItemCount = 10;
	items = vector<InventoryItem*>();
}

Inventory::Inventory(int maxCount)
{
	maxItemCount = maxCount;
	items = vector<InventoryItem*>();
}

Inventory::~Inventory()
{
	items.~vector();
}

bool Inventory::addItem(InventoryItem* item)
{
	for each (InventoryItem* existingItem in items)
	{
		if (existingItem->getID() == item->getID())
		{
			//Item exists, increase its quantity
			existingItem->increaseQuantity(item->getQuantity());
			return true;
		}
	}
	//Item doesn't exist, add item if size allows
	if (items.size() >= maxItemCount) return false;
	items.push_back(item);
	return true;
}

InventoryItem* Inventory::getItem(int id)
{
	for each (InventoryItem* item in items)
	{
		if (item->getID() == id) return item;
	}

	return nullptr;
}

void Inventory::update()
{
	for (unsigned i = 0; i < items.size(); i++)
	{
		if (items[i]->getQuantity() <= 0) items.erase(items.begin() + i);
	}
}

void Inventory::renderItems()
{
	size_t s = 0;
	if (items.size() == s)
	{
		cout << "Your inventory is empty!" << endl;
		return;
	}
	cout << "Your inventory contains:" << endl;
	for each (InventoryItem* item in items)
	{
		cout << "  " << item->getQuantity() << " x " << item->getName() << endl;
	}
}