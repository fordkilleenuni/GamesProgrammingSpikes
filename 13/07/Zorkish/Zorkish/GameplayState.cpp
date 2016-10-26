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
//#include <boost\algorithm\string.hpp>

using namespace std;

size_t _zero = 0;
size_t _one = 1;

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

	if (command == "QUIT")
	{
		cout << "Player decides he/she can no longer go on.." << endl;
		manager.changeState(manager.MAIN_MENU);
		return;
	}

	//split string here to get commands
	vector<string> commands;
	stringstream cmdstream(command);
	string tmp;
	while (getline(cmdstream, tmp, ' '))
		commands.push_back(tmp);
	if (commands[0] == "GO")
	{
		if (commands.size() > _one)
		{
			try
			{
				int new_loc = Adventures::instance().current()->getCurrentLocation().getConnections().at(commands[1]);
				Adventures::instance().current()->setCurrentLocation(new_loc);
				cout << "You go " << commands[1] << endl;
				command = "";
				shouldRender = true;
				return;
			}
			catch (const std::out_of_range&)
			{
				//command not found
				cout << "You can't seem to go that way from here.." << endl;
				command = "";
				shouldRender = true;
				return;
			}
		}
		else
		{
			cout << "Go where?" << endl;
			command = "";
			shouldRender = true;
			return;
		}
	}

	if (commands[0] == "LOOK")
	{
		cout << Adventures::instance().current()->getCurrentLocation().getDetail() << endl;
		command = "";
		shouldRender = true;
		return;
	}

	if (command == "?" || command == "HELP")
	{
		cout << "Available commands:" << endl;
		cout << " - quit" << endl;
		cout << " - hiscore (for testing)" << endl;
		cout << " - go [forward/back/left/right/up/down/over/under/inside/out]" << endl;
		cout << " - look" << endl;
		command = "";
		shouldRender = true;
		return;
	}

	if (command == "HISCORE") //remove this?
	{
		cout << "Player decides he/she can no longer go on.." << endl;
		manager.changeState(manager.NEW_HISCORE);
		return;
	}

	cout << "Unknown command.." << endl;
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