#include "Command.h"
#include "CommandManager.h"
#include <sstream>
#include <iostream>

CommandManager::CommandManager()
{
	commandMap = map<string, Command*>();
	//GO
	Command* cmdPtr = new GoCommand();
	for each (string alias in cmdPtr->getAliases())
		commandMap[alias] = cmdPtr;
	//LOOK
	cmdPtr = new LookCommand();
	for each (string alias in cmdPtr->getAliases())
		commandMap[alias] = cmdPtr;
	//HELP
	cmdPtr = new HelpCommand();
	for each (string alias in cmdPtr->getAliases())
		commandMap[alias] = cmdPtr;
	//PICKUP
	cmdPtr = new PickupCommand();
	for each (string alias in cmdPtr->getAliases())
		commandMap[alias] = cmdPtr;
	//PUT
	cmdPtr = new PutCommand();
	for each (string alias in cmdPtr->getAliases())
		commandMap[alias] = cmdPtr;
	//USE
	cmdPtr = new UseCommand();
	for each (string alias in cmdPtr->getAliases())
		commandMap[alias] = cmdPtr;
}

void CommandManager::processCommand(string command)
{
	vector<string> commands;
	stringstream cmdstream(command);
	string tmp;
	while (getline(cmdstream, tmp, ' '))
		commands.push_back(tmp);

	try
	{
		Command* command = commandMap.at(commands[0]);
		command->process(commands);
	}
	catch (const std::out_of_range&)
	{
		cout << "Unkown command.." << endl;
	}
}