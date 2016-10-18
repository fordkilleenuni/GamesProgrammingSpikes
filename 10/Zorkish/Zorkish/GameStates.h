#pragma once

#include "CommandManager.h"
#include "BaseState.h"
//#include "Player.h"
#include "Entity.h"
#include <vector>
#include <map>
#include "System.h"

using namespace std;

class MainMenuState : public BaseState
{
public:
	MainMenuState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	string command;
};

class SelectAdventureState : public BaseState
{
public:
	SelectAdventureState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	string command;
};

class GameplayState : public BaseState
{
public:
	GameplayState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	bool shouldRenderInitial;
	string command;
	Entity *player;
	Entity *sword;
	HealthSystem *healthSystem;
	DamageSystem *damageSystem;
	CommandManager *cmdManager;
};

class AboutState : public BaseState
{
public:
	AboutState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	char command;
};

class HelpState : public BaseState
{
public:
	HelpState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	char command;
};

class NewHighScoreState : public BaseState
{
public:
	NewHighScoreState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	string command;
};

class HallOfFameState : public BaseState
{
public:
	HallOfFameState();
	void handleInput();
	void update(StateManager &manager);
	void drawState();
private:
	bool shouldRender;
	char command;
};
