#include "Adventure.h"
#include <vector>

using namespace std;

Adventures* Adventures::_instance = 0;

Adventures::Adventures()
{
	currentAdventure = 1;
}

Adventures& Adventures::instance()
{
	if (!_instance)
		_instance = new Adventures;
	return *_instance;
}

void Adventures::addAdventure(int _id, Adventure* _adv)
{
	adventures[_id] = _adv;
}

void Adventures::setCurrentAdventure(int _newid)
{
	currentAdventure = _newid;
}

map<int, Adventure*> Adventures::getAdventures()
{
	return adventures;
}

Adventure* Adventures::current()
{
	if (currentAdventure != -1)
		return adventures[currentAdventure];
	return nullptr;
}

string Adventures::currentName()
{
	return adventures[currentAdventure]->getName();
}

vector<string> Adventures::adventureNames()
{
	vector<string> names;
	for (map<int, Adventure*>::iterator i = adventures.begin(); i != adventures.end(); i++)
	{
		names.push_back(i->second->getName());
	}
	return names;
}

size_t Adventures::count()
{
	return adventures.size();
}
