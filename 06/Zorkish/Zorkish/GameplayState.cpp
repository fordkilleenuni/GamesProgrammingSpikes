#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include "GameItems.h"

using namespace std;

GameplayState::GameplayState()
{
	shouldRender = true;
	shouldRenderInitial = true;
	command = "";
	player = new Player();
}

void GameplayState::handleInput()
{
	if (_kbhit() != 0)
	{
		getline(std::cin, command);
		transform(command.begin(), command.end(), command.begin(), ::toupper);
	}
}

void GameplayState::update(StateManager &manager)
{
	if (command == "") return;

	if (command == "SHOW INVENTORY")
	{
		player->getInventory()->renderItems();
	}

	if (command == "PICKUP SWORD")
	{
		player->getInventory()->addItem(new Sword());
	}

	if (command == "PICKUP KEY")
	{
		player->getInventory()->addItem(new Key());
	}

	if (command == "PICKUP HEALTH POTION")
	{
		player->getInventory()->addItem(new HealthPotion());
	}
	
	if (command == "USE SWORD")
	{
		if (InventoryItem* item = player->getInventory()->getItem(InventoryItem::SWORD))
		{
			item->use();
			player->getInventory()->update();
		}
		else
			cout << "Uh oh, you do not have a sword!" << endl;
	}

	if (command == "USE KEY")
	{
		if (InventoryItem* item = player->getInventory()->getItem(InventoryItem::KEY))
		{
			item->use();
			player->getInventory()->update();
		}
		else
			cout << "Uh oh, you do not have a key!" << endl;
	}

	if (command == "USE HEALTH POTION")
	{
		if (InventoryItem* item = player->getInventory()->getItem(InventoryItem::HEALTHPOTION))
		{
			item->use();
			player->getInventory()->update();
		}
		else
			cout << "Uh oh, you do not have a health potion!" << endl;
	}

	if (command == "LOOK SWORD")
	{
		if (InventoryItem* item = player->getInventory()->getItem(InventoryItem::SWORD))
			cout << item->getDescription() << endl;
		else
			cout << "Uh oh, you do not have a sword!" << endl;
	}

	if (command == "LOOK KEY")
	{
		if (InventoryItem* item = player->getInventory()->getItem(InventoryItem::KEY))
			cout << item->getDescription() << endl;
		else
			cout << "Uh oh, you do not have a key!" << endl;
	}

	if (command == "LOOK HEALTH POTION")
	{
		if (InventoryItem* item = player->getInventory()->getItem(InventoryItem::HEALTHPOTION))
			cout << item->getDescription() << endl;
		else
			cout << "Uh oh, you do not have a health potion!" << endl;
	}

	if (command == "QUIT")
	{
		cout << "Player decides he/she can no longer go on.." << endl;
		manager.changeState(manager.MAIN_MENU);
		return;
	}

	if (command == "HISCORE")
	{
		cout << "Player decides he/she can no longer go on.." << endl;
		manager.changeState(manager.NEW_HISCORE);
		return;
	}

	cout << "Enter your next move > ";
	command = "";
}

void GameplayState::drawState()
{
	if (shouldRenderInitial)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << " Zorkish -- Starting Your Adventure" << endl;
		cout << "--------------------------------------------------" << endl;
		shouldRenderInitial = false;
	}
	if (shouldRender)
	{
		cout << endl;
		cout << "Well, this is a boring adventure.." << endl;
		cout << endl;
		cout << "Enter your next move > ";
		shouldRender = false;
	}
}