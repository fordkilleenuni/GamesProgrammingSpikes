#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "InventoryItem.h"

class Inventory {
public:
	Inventory();
	~Inventory();
	bool addItem(InventoryItem* item);
	InventoryItem* getItem(int id);
	void update();
	void renderItems();
private:
	size_t maxItemCount;
	vector<InventoryItem*> items;
};

#endif // !INVENTORY_H
