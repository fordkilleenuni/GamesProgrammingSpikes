#include "BaseState.h"
#include "GameStates.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

using namespace std;

NewHighScoreState::NewHighScoreState()
{
	NewHighScoreState::shouldRender = true;
	NewHighScoreState::command = "";
}

void NewHighScoreState::handleInput()
{
	if (_kbhit() != 0)
	{
		getline(std::cin, command);
		transform(command.begin(), command.end(), command.begin(), ::toupper);
	}
}

void NewHighScoreState::update(StateManager &manager)
{
	if (command == "") return;
	
	cout << "Well done " << command << "!" << endl;
	//Add player to hiscore list and display hall of fame
	manager.changeState(manager.HALL_FAME);
}

void NewHighScoreState::drawState()
{
	if (shouldRender)
	{
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "           Zorkish -- New High Score" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		cout << "Congratulations! You scored a high score!" << endl;
		cout << "That means you're in the top 10 Zorkish players!" << endl;
		cout << endl;
		cout << "Adventure : Some Adventure" << endl;
		cout << "Score     : over 9000" << endl;
		cout << "Moves     : 99" << endl;
		cout << endl;
		cout << "Please enter your name > ";
		shouldRender = false;
	}
}