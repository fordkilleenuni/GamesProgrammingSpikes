#include "Command.h"
#include "Player.h"
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
		if (cmds[1] == "INVENTORY")
			Player::instance().action(Action::LOOKIN, cmds[1]);
		else
			Adventures::instance().current()->getCurrentLocation().action(Action::LOOKIN, cmds[1]);
	else
		Adventures::instance().current()->getCurrentLocation().action(Action::LOOKAT, "");
}

vector<string> LookCommand::getAliases()
{
	return aliases;
}