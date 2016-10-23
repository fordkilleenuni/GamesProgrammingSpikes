#include "BaseState.h"
#include "GameStates.h"
#include "Adventure.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

SelectAdventureState::SelectAdventureState()
{
	shouldRender = true;
	command = "";
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

	try
	{
		int chosen = stoi(command, nullptr);
		Adventures::instance().getAdventures().at(chosen);
		Adventures::instance().setCurrentAdventure(chosen);
		manager.changeState(manager.GAMEPLAY);
		return;
	}
	catch (const std::exception&)
	{
		//key not found or not an integer.. continue
	}

	command = "";
	cout << "Select number > ";
}

void SelectAdventureState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "           Zorkish -- Select Adventure" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "Choose your adventure:" << endl;
		cout << endl;
		size_t zero = 0;
		if (Adventures::instance().count() == zero) cout << "  Oops! No adventures found.." << endl;
		else
		{
			map<int, Adventure*> tmp = Adventures::instance().getAdventures();
			for (auto i = tmp.begin(); i != tmp.end(); i++)
			{
				cout << "  " << i->first << ". " << i->second->getName() << endl;
			}
		}
		cout << endl;
		cout << "ESC or Enter to go back to the Main Menu" << endl;
		cout << endl;
		cout << "Select number > ";
		shouldRender = false;
	}
}