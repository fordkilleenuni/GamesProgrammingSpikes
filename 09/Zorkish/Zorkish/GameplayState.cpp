#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <string>
#include <algorithm>
#include "GameItems.h"
#include "Adventure.h"
#include "CommandManager.h"

using namespace std;

GameplayState::GameplayState()
{
	shouldRender = true;
	shouldRenderInitial = true;
	command = "";
	Player::instance();
	cmdManager = new CommandManager();
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