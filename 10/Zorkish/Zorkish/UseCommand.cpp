#include "Command.h"
#include "Sizes.h"
#include <stdio.h>
#include <iostream>
#include "Messenger.h"

UseCommand::UseCommand()
{
	aliases.push_back("USE");
	aliases.push_back("ACTIVATE");
	aliases.push_back("ENABLE");
}

void UseCommand::process(vector<string> cmds)
{
	if (cmds[1] == "SWORD")
	{
		Messenger::instance().sendMessage(new Message(Tag::DAMAGE, "10"));
	}
	if (cmds[1] == "POTION")
	{
		Messenger::instance().sendMessage(new Message(Tag::HEALTH, "5"));
	}
	//if (cmds.size() > Sizes::_one)
	//	cout << "You use " << cmds[1] << endl;
	//else
	//	cout << "Use what?" << endl;
}

vector<string> UseCommand::getAliases()
{
	return aliases;
}