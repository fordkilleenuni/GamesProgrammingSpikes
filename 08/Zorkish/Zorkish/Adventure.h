#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Location
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
private:
	int id;
	string name;
	string detail;
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