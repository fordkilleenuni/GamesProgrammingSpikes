#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <string>
#include <algorithm>
//#include "GameItems.h"
#include "Adventure.h"
#include "CommandManager.h"
#include "Components.h"
#include "System.h"
#include "Messenger.h"

using namespace std;

GameplayState::GameplayState()
{
	shouldRender = true;
	shouldRenderInitial = true;
	command = "";
	cmdManager = new CommandManager();

	//Systems
	healthSystem = new HealthSystem;
	damageSystem = new DamageSystem;
	//Player
	player = new Entity;
	HealthComponent* health = new HealthComponent;
	player->addComponent(HealthComponent::IDENTIFIER, health);
	healthSystem->add(health);
	DamageableComponent* dmgable = new DamageableComponent;
	player->addComponent(DamageableComponent::IDENTIFIER, dmgable);
	//Sword
	sword = new Entity;
	DamageComponent* dmg = new DamageComponent;
	sword->addComponent(DamageComponent::IDENTIFIER, dmg);
	damageSystem->add(dmg);

	Messenger::instance().addListener(player);
	Messenger::instance().addListener(sword);
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

	if (command == "QUIT")
	{
		manager.changeState(manager.MAIN_MENU);
		return;
	}

	cmdManager->processCommand(command);

	command = "";
	shouldRender = true;

	//Update systems
	damageSystem->update();
	healthSystem->update();
}

void GameplayState::drawState()
{
	if (shouldRenderInitial)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "        Zorkish -- Starting Your Adventure" << endl;
		cout << "--------------------------------------------------" << endl << endl;
		cout << "Starting : " << Adventures::instance().currentName() << endl;
		shouldRenderInitial = false;
	}
	if (shouldRender)
	{
		cout << endl;
		cout << " -> ";
		shouldRender = false;
	}
}