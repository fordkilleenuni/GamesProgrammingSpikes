#include "Items.h"

Sword::Sword()
{
	name = "";
}

void Sword::action(Action _action, string _name)
{
	if (_action == LOOKAT)
		cout << "A long sword with a sharp, shiny blade." << endl;
}

Bread::Bread()
{
	name = "";
}

void Bread::action(Action _action, string _name)
{
	if (_name != name)
		return;

	if (_action == LOOKAT)
		cout << "A tasty looking lump of bread." << endl;
}