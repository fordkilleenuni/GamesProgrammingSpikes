#pragma once

#include <iostream>
#include <string>
#include "InventoryItem.h"

using namespace std;

class Sword : public InventoryItem {
public:
	Sword();
	~Sword();
	int getID();
	string getName();
	string getDescription();
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
	int getID();
	string getName();
	string getDescription();
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
	int getID();
	string getName();
	string getDescription();
	int getQuantity();
	bool increaseQuantity(int amount);
	void use();
private:
	string name;
	string description;
	int quantity;
};
