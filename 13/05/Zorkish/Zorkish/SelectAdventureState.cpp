#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

SelectAdventureState::SelectAdventureState()
{
	SelectAdventureState::shouldRender = true;
	SelectAdventureState::command = "";
}

void SelectAdventureState::handleInput()
{
	if (_kbhit() != 0)
	{
		getline(std::cin, command);
		transform(command.begin(), command.end(), command.begin(), ::toupper);
	}
}

void SelectAdventureState::update(StateManager &manager)
{
	if (command == "") return;

	if (command == "1" || command == "2" || command == "3")
	{
		manager.changeState(manager.GAMEPLAY);
		return;
	}

	cout << "Select 1-3 > ";
	command = "";
}

void SelectAdventureState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << " Zorkish -- Select Adventure" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "Choose your adventure:" << endl;
		cout << endl;
		cout << "  1. Giant World" << endl;
		cout << "  2. Upside Down World" << endl;
		cout << "  3. Dark World" << endl;
		cout << endl;
		cout << "ESC or Enter to go back to the Main Menu" << endl;
		cout << endl;
		cout << "Select 1-3 > ";
		shouldRender = false;
	}
}