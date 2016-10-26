#include "Adventure.h"

using namespace std;

Location::Location() 
	: id(1)
	, name("")
	, detail("")
	, connections(new map<string, int>())
{
}

Location::Location(int _id, string _name, string _detail)
	: id(_id)
	, name(_name)
	, detail(_detail)
	, connections(new map<string, int>())
{
}

Location::~Location()
{
	delete connections;
}

void Location::setId(int _id)
{
	id = _id;
}

int Location::getId()
{
	return id;
}

void Location::setName(string _name)
{
	name = _name;
}

string Location::getName()
{
	return name;
}

void Location::setDetail(string _detail)
{
	detail = _detail;
}

string Location::getDetail()
{
	return detail;
}

void Location::addConnection(string command, int connection)
{
	(*connections)[command] = connection;
}

map<string, int>& Location::getConnections()
{
	return *connections;
}

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

map<int, Location*> Adventure::getAllLocations()
{
	return locations;
}

Location& Adventure::getCurrentLocation()
{
	return *locations[currentLocation];
}
