#pragma once
#ifndef GAMEITEMS_H
#define GAMEITEMS_H

#include <iostream>
#include <string>
#include "InventoryItem.h"

using namespace std;

class Sword : public InventoryItem {
public:
	Sword();
	~Sword();
	int getID() const;
	string getName() const;
	string getDescription() const;
	int getQuantity();
	bool increaseQuantity(int amount);
	void use();
private:
	string name;
	string description;
	int quantity;
	int damage;
};

class HealthPotion : public InventoryItem {
public:
	HealthPotion();
	~HealthPotion();
	int getID() const;
	string getName() const;
	string getDescription() const;
	int getQuantity();
	bool increaseQuantity(int amount);
	void use();
private:
	string name;
	string description;
	int quantity;
	int healthToRestore;
};

class Key : public InventoryItem {
public:
	Key();
	~Key();
	int getID() const;
	string getName() const;
	string getDescription() const;
	int getQuantity();
	bool increaseQuantity(int amount);
	void use();
private:
	string name;
	string description;
	int quantity;
};

#endif // !GAMEITEMS_H
