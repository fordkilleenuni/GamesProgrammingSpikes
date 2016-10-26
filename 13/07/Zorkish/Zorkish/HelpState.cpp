#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

HelpState::HelpState()
{
	HelpState::shouldRender = true;
	HelpState::command = 0;
}

void HelpState::handleInput()
{
	if (_kbhit() != 0)
	{
		command = _getch();
	}
}

void HelpState::update(StateManager &manager)
{
	if (command == 0) return;
	//If Enter or ESC pressed, go back to main menu
	if (command == 13 || command == 27) manager.changeState(manager.MAIN_MENU);
}

void HelpState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "                Zorkish -- Help" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "The following commands are supported:" << endl;
		cout << endl;
		cout << " - quit" << endl;
		cout << " - hiscore (for testing)" << endl;
		cout << " - go [forward/back/left/right/up/down/over/under/inside/out]" << endl;
		cout << " - look" << endl;
		cout << endl;
		cout << "Press ESC or Enter to go back to the Main Menu.." << endl;
		shouldRender = false;
	}
}