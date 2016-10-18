#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Component.h"

using namespace std;

class Location : public Container
{
public:
	Location();
	Location(int _id, string _name, string _detail);
	~Location();
	void setId(int _id);
	int getId();
	void setName(string _name);
	string getName();
	void setDetail(string _detail);
	string getDetail();
	void addConnection(string command, int connection);
	map<string, int>& getConnections();
	void action(Action _action, string _name);
private:
	int locid;
	string locname;
	string locdetail;
	map<string, int> *connections;
};

class Adventure
{
public:
	Adventure();
	~Adventure();
	void setName(string _name);
	string getName();
	void addLocation(int id, Location* loc);
	map<int, Location*> getAllLocations();
	Location &getCurrentLocation();
	void setCurrentLocation(int _newloc);
	Location &getLocation(int _id);
private:
	string name;
	int currentLocation;
	map<int, Location*> locations;
};

class Adventures
{
public:
	static Adventures &instance();
	void addAdventure(int _id, Adventure* _adv);
	void setCurrentAdventure(int _newid);
	map<int, Adventure*> getAdventures();
	Adventure* current();
	string currentName();
	vector<string> adventureNames();
	size_t count();
private:
	Adventures();
	static Adventures *_instance;
	int currentAdventure;
	map<int, Adventure*> adventures;
};