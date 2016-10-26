#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

class MainMenuState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void MainMenuState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void MainMenuState::update(StateManager manager)
	{
		if (command != "")
		{
			if (command == "1")
			{
				manager.changeState(SelectAdventureState());
			}
			if (command == "2")
			{
				manager.changeState(HallOfFameState());
			}
			if (command == "3")
			{
				manager.changeState(HelpState());
			}
			if (command == "4")
			{
				manager.changeState(AboutState());
			}
			if (command == "5")
			{
				manager.quitRequested();
			}
		}
	}

	virtual void MainMenuState::drawState()
	{
		if (shouldRender)
		{
			cout << "Zorkish -- Main Menu" << endl;
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
			cout << "Select 1-5 > " << endl;
			shouldRender = false;
		}
	}
};

class SelectAdventureState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void SelectAdventureState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void SelectAdventureState::update(StateManager manager)
	{
		if (command != "")
		{

		}
	}

	virtual void SelectAdventureState::drawState()
	{
		if (shouldRender)
		{
			cout << "Zorkish -- Select Adventure" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << endl;
			cout << "Choose your adventure:" << endl;
			cout << endl;
			cout << "  1. Giant World" << endl;
			cout << "  2. Upside Down World" << endl;
			cout << "  3. Dark World" << endl;
			cout << endl;
			cout << "  ESC/Enter. Back to Main Menu" << endl;
			cout << endl;
			cout << "Select 1-3 > " << endl;
			shouldRender = false;
		}
	}
};

class GameplayState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void GameplayState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void GameplayState::update(StateManager manager)
	{
		if (command != "")
		{

		}
	}

	virtual void GameplayState::drawState()
	{
		if (shouldRender)
		{
			cout << "This is a boring adventure.." << endl;
			shouldRender = false;
		}
	}
};

class AboutState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void AboutState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void AboutState::update(StateManager manager)
	{
		if (command != "")
		{

		}
	}

	virtual void AboutState::drawState()
	{
		if (shouldRender)
		{
			cout << "Zorkish -- About" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << endl;
			cout << "Written by : Ford Killeen [9731822]" << endl;
			cout << endl;
			cout << "Press ESC or Enter to go back to the Main Menu" << endl;
			cout << "  2. Hall of Fame" << endl;
			shouldRender = false;
		}
	}
};

class HelpState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void HelpState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void HelpState::update(StateManager manager)
	{
		if (command != "")
		{
			if (command == "1")
			{
				//manager.changeState(new state...)
			}
			if (command == "2")
			{
				//manager.changeState(new state...)
			}
			if (command == "3")
			{
				//manager.changeState(new state...)
			}
			if (command == "4")
			{
				//manager.changeState(new state...)
			}
			if (command == "5")
			{
				//manager.changeState(new state...)
			}
		}
	}

	virtual void HelpState::drawState()
	{
		if (shouldRender)
		{
			cout << "Zorkish -- Help" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << endl;
			cout << "The following commands are supported:" << endl;
			cout << endl;
			cout << "  quit" << endl;
			cout << "  hiscore (for testing)" << endl;
			cout << endl;
			cout << "Press ESC or Enter to go back to the Main Menu " << endl;
			shouldRender = false;
		}
	}
};

class NewHighScoreState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void NewHighScoreState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void NewHighScoreState::update(StateManager manager)
	{
		if (command != "")
		{
			
		}
	}

	virtual void NewHighScoreState::drawState()
	{
		if (shouldRender)
		{
			cout << "Zorkish -- Main Menu" << endl;
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
			cout << "Select 1-5 > " << endl;
			shouldRender = false;
		}
	}
};

class HallOfFameState : public BaseState
{
	bool shouldRender = false;
	string command = "";

	virtual void HallOfFameState::handleInput()
	{
		if (_kbhit() != 0)
		{
			getline(std::cin, command);
			transform(command.begin(), command.end(), command.begin(), ::toupper);
		}
	}

	virtual void HallOfFameState::update(StateManager manager)
	{
		if (command != "")
		{
			
		}
	}

	virtual void HallOfFameState::drawState()
	{
		if (shouldRender)
		{
			cout << "Zorkish -- Hall Of Fame" << endl;
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
			cout << "Select 1-5 > " << endl;
			shouldRender = false;
		}
	}
};