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
		Messenger::instance().sendAnnouncement(new Message(Tag::DAMAGE, "10"));
	}
	if (cmds[1] == "POTION")
	{
		Messenger::instance().sendAnnouncement(new Message(Tag::HEALTH, "5"));
	}
	if (cmds[1] == "PAPER")
	{
		cout << "You leave a message on a note." << endl;
		Messenger::instance().addBlackboardMessage(new Message(Tag::ALL, cmds[2]));
	}
	if (cmds[1] == "EYES")
	{
		cout << "You look at the paper note, it says:" << endl;
		map<int, Message*> msgs = Messenger::instance().viewBlackboard();
		for (map<int, Message*>::iterator i = msgs.begin(); i != msgs.end(); i++)
			cout << " - " << i->second->getContents() << endl;
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