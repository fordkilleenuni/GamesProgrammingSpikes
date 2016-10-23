#pragma once
#include <vector>
#include <string>

using namespace std;

class Command
{
public:
	virtual void process(vector<string> cmds) = 0;
	virtual vector<string> getAliases() = 0;
};

class GoCommand : public Command
{
private:
	vector<string> aliases;
public:
	GoCommand();
	void process(vector<string> cmds);
	vector<string> getAliases();
};

class LookCommand : public Command
{
private:
	vector<string> aliases;
public:
	LookCommand();
	void process(vector<string> cmds);
	vector<string> getAliases();
};

class HelpCommand : public Command
{
private:
	vector<string> aliases;
public:
	HelpCommand();
	void process(vector<string> cmds);
	vector<string> getAliases();
};

class PickupCommand : public Command
{
private:
	vector<string> aliases;
public:
	PickupCommand();
	void process(vector<string> cmds);
	vector<string> getAliases();
};

class UseCommand : public Command
{
private:
	vector<string> aliases;
public:
	UseCommand();
	void process(vector<string> cmds);
	vector<string> getAliases();
};