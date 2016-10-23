#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

MainMenuState::MainMenuState()
{
	shouldRender = true;
	command = "";
}

void MainMenuState::handleInput()
{
	if (_kbhit() != 0)
	{
		//Read input from cin
		getline(std::cin, command);
		transform(command.begin(), command.end(), command.begin(), ::toupper);
	}
}

void MainMenuState::update(StateManager &manager)
{
	if (command == "") return;

	//Update game based on given command
	if (command == "1")
	{
		manager.changeState(manager.SELECT_ADVENTURE);
		return;
	}
	if (command == "2")
	{
		manager.changeState(manager.HALL_FAME);
		return;
	}
	if (command == "3")
	{
		manager.changeState(manager.HELP);
		return;
	}
	if (command == "4")
	{
		manager.changeState(manager.ABOUT);
		return;
	}
	if (command == "5")
	{
		manager.quitRequested();
		return;
	}

	//If no valid command, ask for input again..
	cout << "Select 1-5 > ";
	command = "";
}

void MainMenuState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "              Zorkish -- Main Menu" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "Welcome to Zorkish Adventures!" << endl;
		cout << endl;
		cout << "  1. Choose your adventure" << endl;
		cout << "  2. Hall of Fame" << endl;
		cout << "  3. Help" << endl;
		cout << "  4. About" << endl;
		cout << "  5. Quit" << endl;
		cout << endl;
		cout << "Select 1-5 > ";
		shouldRender = false;
	}
}