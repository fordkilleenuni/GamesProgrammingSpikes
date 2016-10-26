#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

GameplayState::GameplayState()
{
	GameplayState::shouldRender = true;
	GameplayState::shouldRenderInitial = true;
	GameplayState::command = "";
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