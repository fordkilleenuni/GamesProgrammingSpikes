#pragma once
#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>

using namespace std;

class InventoryItem {
public:
	virtual int getID() = 0;
	virtual string getName() = 0;
	virtual string getDescription() = 0;
	virtual int getQuantity() = 0;
	virtual bool increaseQuantity(int amount) = 0;
	virtual void use() = 0;
	//Subclass IDs
	static const int SWORD = 1;
	static const int HEALTHPOTION = 2;
	static const int KEY = 3;
};

#endif // !INVENTORYITEM_H
