#include "Component.h"
#include "Sizes.h"

Item::Item()
{
	name = "";
}

void Item::action(Action _action, string _name)
{
	cout << "Item: " << name << endl;
}

string Item::get_name()
{
	return name;
}

void Item::set_name(string _name)
{
	name = _name;
}

Container::Container()
{
	name = "";
	locked = false;
	open = true;
	items = map<string, Component*>();
}

Container::Container(bool _locked, bool _open)
{
	name = "";
	locked = _locked;
	open = _open;
	items = map<string, Component*>();
}

void Container::action(Action _action, string _name)
{
	cout << "Container:" << name << " contains " << items.size() << endl;
	for (map<string, Component*>::iterator i = items.begin(); i != items.end(); i++)
		i->second->action(Action::LOOKAT, "");
}

string Container::get_name()
{
	return name;
}

void Container::set_name(string _name)
{
	name = _name;
}

void Container::add(string _name, Component * _cpnt)
{
	items[_name] = _cpnt;
}

bool Container::remove(string _name)
{
	if (items.erase(_name) > Sizes::_zero)
		return true;
	return false;
}

Component * Container::get(string _name)
{
	for (map<string, Component*>::iterator i = items.begin(); i != items.end(); i++)
		if (i->first == _name)
			return i->second;
	return nullptr;
}

void Container::printitems()
{
	for (map<string, Component*>::iterator i = items.begin(); i != items.end(); i++)
	{
		cout << " - " << i->second->get_name() << endl;
	}
}
