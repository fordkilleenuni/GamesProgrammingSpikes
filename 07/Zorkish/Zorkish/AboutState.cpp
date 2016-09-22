#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

AboutState::AboutState()
{
	AboutState::shouldRender = true;
	AboutState::command = 0;
}

void AboutState::handleInput()
{
	if (_kbhit() != 0)
	{
		command = _getch();
	}
}

void AboutState::update(StateManager &manager)
{
	if (command == 0) return;
	//If Enter or ESC pressed, go back to main menu
	if (command == 13 || command == 27) manager.changeState(manager.MAIN_MENU);
}

void AboutState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "              Zorkish -- About" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "Written by : Ford Killeen [9731822]" << endl;
		cout << endl;
		cout << "Press ESC or Enter to go back to the Main Menu.." << endl;
		shouldRender = false;
	}
}