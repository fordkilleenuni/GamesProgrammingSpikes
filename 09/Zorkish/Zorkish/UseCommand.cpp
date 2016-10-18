#include "Command.h"
#include "Sizes.h"
#include <stdio.h>
#include <iostream>

UseCommand::UseCommand()
{
	aliases.push_back("USE");
	aliases.push_back("ACTIVATE");
	aliases.push_back("ENABLE");
}

void UseCommand::process(vector<string> cmds)
{
	if (cmds.size() > Sizes::_one)
		cout << "You use " << cmds[1] << endl;
	else
		cout << "Use what?" << endl;
}

vector<string> UseCommand::getAliases()
{
	return aliases;
}