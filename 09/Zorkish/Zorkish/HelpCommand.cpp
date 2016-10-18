#include "Command.h"
#include <stdio.h>
#include <iostream>

HelpCommand::HelpCommand()
{
	aliases.push_back("HELP");
	aliases.push_back("?");
}

void HelpCommand::process(vector<string> cmds)
{
	cout << "Available commands:" << endl;
	cout << " - quit" << endl;
	cout << " - hiscore (for testing)" << endl;
	cout << " - go [forward/back/left/right/up/down/over/under/inside/out]" << endl;
	cout << " - look" << endl;
}

vector<string> HelpCommand::getAliases()
{
	return aliases;
}