#include "StateManager.h"
#include "GameStates.h"
#include <string>

using namespace std;

const string StateManager::MAIN_MENU = "main_menu";
const string StateManager::SELECT_ADVENTURE = "select_adventure";
const string StateManager::GAMEPLAY = "gameplay";
const string StateManager::HELP = "help";
const string StateManager::ABOUT = "about";
const string StateManager::NEW_HISCORE = "new_hiscore";
const string StateManager::HALL_FAME = "hall_of_fame";

BaseState *currentState;

StateManager::StateManager() 
{
	gameActive = true;
	currentState = new MainMenuState();
	nextState = "";
}

StateManager::~StateManager()
{
	delete currentState;
}

void StateManager::update()
{
	currentState->handleInput();
	currentState->update(*this);
	currentState->drawState();
	checkNextState();
}

void StateManager::changeState(string newState)
{
	nextState = newState;
}

bool StateManager::gameIsActive()
{
	return gameActive;
}

void StateManager::quitRequested()
{
	gameActive = false;
}

void StateManager::checkNextState()
{
	if (nextState == "") return;

	if (nextState == MAIN_MENU)
	{
		currentState = new MainMenuState();
		nextState = "";
		return;
	}

	if (nextState == SELECT_ADVENTURE)
	{
		currentState = new SelectAdventureState();
		nextState = "";
		return;
	}

	if (nextState == GAMEPLAY)
	{
		currentState = new GameplayState();
		nextState = "";
		return;
	}

	if (nextState == HELP) 
	{
		currentState = new HelpState();
		nextState = "";
		return;
	}

	if (nextState == ABOUT) 
	{
		currentState = new AboutState();
		nextState = "";
		return;
	}

	if (nextState == NEW_HISCORE) 
	{
		currentState = new NewHighScoreState();
		nextState = "";
		return;
	}

	if (nextState == HALL_FAME) 
	{
		currentState = new HallOfFameState();
		nextState = "";
		return;
	}
}