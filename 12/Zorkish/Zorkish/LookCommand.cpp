#include "Command.h"
#include "Adventure.h"
#include "Sizes.h"
#include <stdio.h>

LookCommand::LookCommand()
{
	aliases.push_back("LOOK");
	aliases.push_back("CHECK");
	aliases.push_back("INVESTIGATE");
	aliases.push_back("EXAMINE");
}

void LookCommand::process(vector<string> cmds)
{
	if (cmds.size() > Sizes::_one)
		cout << "You look at " << cmds[1] << endl;
	else
		cout << "Look where?" << endl;
}

vector<string> LookCommand::getAliases()
{
	return aliases;
}