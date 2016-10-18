#include "Command.h"
#include "Adventure.h"
#include "Sizes.h"
#include <stdio.h>
#include <iostream>

PickupCommand::PickupCommand()
{
	aliases.push_back("PICKUP");
	aliases.push_back("TAKE");
	aliases.push_back("GRAB");
	aliases.push_back("STEAL");
	aliases.push_back("SNATCH");
	aliases.push_back("PLUCK");
}

void PickupCommand::process(vector<string> cmds)
{
	if (cmds.size() > Sizes::_one)
		Adventures::instance().current()->getCurrentLocation().action(Action::TAKE, cmds[1]);
	else
		cout << "Pickup what?" << endl;
}

vector<string> PickupCommand::getAliases()
{
	return aliases;
}