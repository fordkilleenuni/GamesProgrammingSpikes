#include "Containers.h"
#include "Player.h"

Chest::Chest()
{
	name = "";
	locked = false;
	open = true;
	items = map<string, Component*>();
}

Chest::Chest(bool _locked, bool _open)
{
	name = "";
	locked = _locked;
	open = _open;
	items = map<string, Component*>();
}

void Chest::action(Action _action, string _name)
{
	//if (_name != name)
	//{
	//	for (map<string, Component*>::iterator i = items.begin(); i != items.end(); i++)
	//		i->second->action(_action, _name);
	//	return;
	//}

	switch (_action)
	{
	case OPEN:
		if (locked)
		{
			cout << "You try, but the chest is locked." << endl;
			return;
		}
		if (open)
		{
			cout << "How convenient, the chest was already open." << endl;
			return;
		}
		open = true;
		cout << "You manage to open the chest. What treasures lie within?" << endl;
		break;
	case LOOKAT:
		if (locked)
			cout << "You see a locked chest. What could be inside?" << endl;
		else
			cout << "You see a chest. What could be inside?" << endl;
		break;
	case LOOKIN:
		if (open)
		{
			cout << "You look inside the chest and see:" << endl;
			printitems();
			return;
		}
		cout << "You attempt to look in the chest, but unfortunately it's still closed." << endl;
		break;
	case UNLOCK:
		if (locked)
		{
			cout << "You somehow manage to unlock the chest." << endl;
			locked = false;
			return;
		}
		cout << "That was silly, the chest was already unlocked." << endl;
		break;
	case TAKE:
		if (!locked && open)
		{
			Component* comp;

			comp = get(_name);
			if (comp != 0)
			{
				Player::instance().add(comp->get_name(), comp);
				remove(_name);
				cout << "You take the " << _name << endl;
				return;
			}
			cout << "Oops, you can't find a " << _name << endl;
		}
	}
}