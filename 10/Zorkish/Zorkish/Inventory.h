#pragma once

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
