#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

enum Action { OPEN, LOOKIN, LOOKAT, UNLOCK, TAKE };

class Component
{
public:
	virtual void action(Action _action, string _name) = 0;
	virtual string get_name() = 0;
	virtual void set_name(string _name) = 0;
protected:
	string name;
};

class Item : public Component
{
public:
	Item();
	virtual void action(Action _action, string _name);
	string get_name();
	void set_name(string _name);
};

class Container : public Component
{
public:
	Container();
	Container(bool _locked, bool _open);
	virtual void action(Action _action, string _name);
	string get_name();
	void set_name(string _name);
	void add(string _name, Component *_cpnt);
	bool remove(string _name);
	Component *get(string _name);
protected:
	map<string, Component*> items;
	bool locked;
	bool open;
	void printitems();
};