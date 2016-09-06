#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <string>
using namespace std;

class StateManager
{
public:
	StateManager();
	~StateManager();
	void update();
	void changeState(string newState);
	bool gameIsActive();
	void quitRequested();
	static const string MAIN_MENU;
	static const string SELECT_ADVENTURE;
	static const string GAMEPLAY;
	static const string HELP;
	static const string ABOUT;
	static const string NEW_HISCORE;
	static const string HALL_FAME;
private:
	void checkNextState();
	bool gameActive;
	string nextState;
};

#endif // !STATEMANAGER_H