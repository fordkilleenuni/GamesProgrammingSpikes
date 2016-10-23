#pragma once
#include <map>
#include <string>
#include "Command.h"

using namespace std;

class CommandManager
{
private:
	map<string, Command*> commandMap;
public:
	CommandManager();
	void processCommand(string command);
};