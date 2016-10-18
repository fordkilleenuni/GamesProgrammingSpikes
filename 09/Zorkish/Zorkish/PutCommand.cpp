#include "Command.h"
#include "Adventure.h"
#include "Player.h"
#include "Sizes.h"
#include <stdio.h>

PutCommand::PutCommand()
{
	aliases.push_back("PUT");
	aliases.push_back("PLACE");
	aliases.push_back("DROP");
	aliases.push_back("THROW");
}

void PutCommand::process(vector<string> cmds)
{
	if (cmds.size() == Sizes::_four)
	{
		try
		{
			Component* comp = Player::instance().get(cmds[1]);
			Location loc = Adventures::instance().current()->getCurrentLocation();
			Container* cont = (Container*) loc.get(cmds[3]);
			cont->add(comp->get_name(), comp);
			Player::instance().remove(cmds[1]);
			cout << "You put the " << cmds[1] << " in the " << cmds[3] << endl;
		}
		catch (const std::exception&)
		{
			cout << "Oops, you can't find either the item or container" << endl;
		}
	}
	else if (cmds.size() == Sizes::_two)
	{
		try
		{
			Component* comp = Player::instance().get(cmds[1]);
			Adventures::instance().current()->getCurrentLocation().add(comp->get_name(), comp);
			Player::instance().remove(cmds[1]);
			cout << "You drop a " << cmds[1] << endl;
		}
		catch (const std::exception&)
		{
			cout << "Oops, can't find a " << cmds[1] << endl;
		}
	}
	else
		cout << "Put what?" << endl;
}

vector<string> PutCommand::getAliases()
{
	return aliases;
}