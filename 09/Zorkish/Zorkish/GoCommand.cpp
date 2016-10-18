#include "Command.h"
#include "Adventure.h"
#include <stdio.h>
#include "Sizes.h"

GoCommand::GoCommand()
{
	//actions
	aliases.push_back("GO");
	aliases.push_back("MOVE");
	aliases.push_back("WALK");
	aliases.push_back("RUN");
	aliases.push_back("SNEAK");
	//directions
	aliases.push_back("FORWARD");
	aliases.push_back("BACK");
	aliases.push_back("LEFT");
	aliases.push_back("RIGHT");
	aliases.push_back("UP");
	aliases.push_back("DOWN");
	aliases.push_back("UNDER");
	aliases.push_back("INSIDE");
	aliases.push_back("OUT");
}

void GoCommand::process(vector<string> cmds)
{
	string tmp;
	for (size_t s = 0; s < cmds.size(); s++)
	{
		tmp = cmds[s];

		if ((tmp == "GO" || tmp == "MOVE" || tmp == "WALK" || tmp == "RUN" || tmp == "SNEAK"))
			if (cmds.size() == Sizes::_one)
			{
				cout << "Go where?" << endl;
				return;
			}
			else
				continue;

		try
		{
			int new_loc = Adventures::instance().current()->getCurrentLocation().getConnections().at(tmp);
			Adventures::instance().current()->setCurrentLocation(new_loc);
			cout << "You go " << tmp << endl;
			return;
		}
		catch (const std::out_of_range&)
		{
			//command not found
			cout << "You can't go " << tmp << " from here.." << endl;
			return;
		}
	}
}

vector<string> GoCommand::getAliases()
{
	return aliases;
}