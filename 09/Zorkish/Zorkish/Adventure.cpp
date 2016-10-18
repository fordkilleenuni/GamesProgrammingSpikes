#include "Adventure.h"

using namespace std;

// Location -----------------------------------------------------
Location::Location() 
	: locid(1)
	, locname("")
	, locdetail("")
	, connections(new map<string, int>())
{
	name = "";
	locked = false;
	open = true;
	items = map<string, Component*>();
}

Location::Location(int _id, string _name, string _detail)
	: locid(_id)
	, locname(_name)
	, locdetail(_detail)
	, connections(new map<string, int>())
{
	name = "";
	locked = false;
	open = true;
	items = map<string, Component*>();
}

Location::~Location()
{
	delete connections;
}

void Location::setId(int _id)
{
	locid = _id;
}

int Location::getId()
{
	return locid;
}

void Location::setName(string _name)
{
	locname = _name;
}

string Location::getName()
{
	return locname;
}

void Location::setDetail(string _detail)
{
	locdetail = _detail;
}

string Location::getDetail()
{
	return locdetail;
}

void Location::addConnection(string command, int connection)
{
	(*connections)[command] = connection;
}

map<string, int>& Location::getConnections()
{
	return *connections;
}

void Location::action(Action _action, string _name)
{
	if (_name == "")
	{
		cout << getDetail() << endl << endl;
		cout << "You look around and see:" << endl;
		printitems();
		return;
	}
	for (map<string, Component*>::iterator i = items.begin(); i != items.end(); i++)
		i->second->action(_action, _name);
}

// Adventure -----------------------------------------------------
Adventure::Adventure()
{
	name = "";
	currentLocation = 1;
}

Adventure::~Adventure()
{
}

void Adventure::setName(string _name)
{
	name = _name;
}

string Adventure::getName()
{
	return name;
}

void Adventure::addLocation(int id, Location* loc)
{
	locations[id] = loc;
}

void Adventure::setCurrentLocation(int _newloc)
{
	currentLocation = _newloc;
}

Location& Adventure::getLocation(int _id)
{
	return *locations[_id];
}

map<int, Location*> Adventure::getAllLocations()
{
	return locations;
}

Location& Adventure::getCurrentLocation()
{
	return *locations[currentLocation];
}
