#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

HallOfFameState::HallOfFameState()
{
	HallOfFameState::shouldRender = true;
	HallOfFameState::command = 0;
}

void HallOfFameState::handleInput()
{
	if (_kbhit() != 0)
	{
		command = _getch();
	}
}

void HallOfFameState::update(StateManager &manager)
{
	if (command == 0) return;
	//If Enter or ESC pressed, go back to main menu
	if (command == 13 || command == 27) manager.changeState(manager.MAIN_MENU);
}

void HallOfFameState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "            Zorkish -- Hall Of Fame" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "Top 10 Zorkish Adventurers" << endl;
		cout << endl;
		cout << "  1. Freddie, Giant World, 5000" << endl;
		cout << "  2. Bobby, Giant World, 4500" << endl;
		cout << "  3. Frankie, Giant World, 4100" << endl;
		cout << "  4. Joey, Giant World, 4000" << endl;
		cout << "  5. Kristy, Giant World, 3990" << endl;
		cout << "  6. Cathy, Giant World, 3700" << endl;
		cout << "  7. Johny, Giant World, 3500" << endl;
		cout << "  8. Jackie, Giant World, 3333" << endl;
		cout << "  9. Jenny, Giant World, 3000" << endl;
		cout << "  10. Benny, Upside Down World, 10" << endl;
		cout << endl;
		cout << "Press ESC or Enter to go back to the Main Menu.." << endl;
		shouldRender = false;
	}
}