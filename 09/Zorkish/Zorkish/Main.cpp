#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <string>
#include <algorithm>
#include "StateManager.h"
#include "Player.h"
#include "Adventure.h"
#include "Items.h"
#include "Containers.h"

using namespace std;

void loadAvdentures()
{
	int adventurenum = 1;
	ifstream toload;
	toload.open("C:\\Adventures\\ToLoad.txt");
	if (toload.is_open())
	{
		while (!toload.eof())
		{
			string advfile;
			getline(toload, advfile);
			//Read adventure file
			Adventure* adventure = new Adventure();
			std::ifstream file;
			file.open(advfile);
			if (file.is_open())
			{
				bool firstline = true;
				bool entities = false;
				string line;
				map<string, Container*> temp_entities;

				while (!file.eof())
				{
					getline(file, line);
					//Set adventure name or get location data
					if (firstline)
					{
						adventure->setName(line);
						firstline = false;
					}
					else
					{
						if (line == "Entities")
							entities = true;
						else
						{
							if (!entities)
							{
								Location* loc = new Location();
								stringstream linestream(line);
								string tmp;
								vector<string> locdata;
								while (getline(linestream, tmp, '\t'))
									locdata.push_back(tmp);
								int _id = stoi(locdata[0], nullptr);
								loc->setId(_id);
								loc->setName(locdata[1]);
								loc->setDetail(locdata[2]);
								vector<string> conns;
								stringstream connstream(locdata[3]);
								while (getline(connstream, tmp, '+'))
									conns.push_back(tmp);
								for (size_t i = 0; i < conns.size(); i++)
								{
									vector<string> conn;
									stringstream comstream(conns[i]);
									while (getline(comstream, tmp, '>'))
										conn.push_back(tmp);
									_id = stoi(conn[1], nullptr);
									transform(conn[0].begin(), conn[0].end(), conn[0].begin(), ::toupper);
									loc->addConnection(conn[0], _id);
								}
								adventure->addLocation(loc->getId(), loc);
								temp_entities[locdata[0]] = loc;
							}
							else
							{
								stringstream linestream(line);
								string tmp;
								vector<string> entdata;
								while (getline(linestream, tmp, '\t'))
									entdata.push_back(tmp);
								if (entdata[1] == "CHST")
								{
									Chest *thing = new Chest();
									thing->set_name(entdata[0]);
									try
									{
										temp_entities[entdata[2]]->add(entdata[0], thing);
										temp_entities[entdata[0]] = thing;
									}
									catch (const std::exception&)
									{
									}
								}
								else if (entdata[1] == "SWRD")
								{
									Sword *thing = new Sword();
									thing->set_name(entdata[0]);
									try
									{
										temp_entities[entdata[2]]->add(entdata[0], thing);
									}
									catch (const std::invalid_argument&)
									{
									}
								}
								else if (entdata[1] == "BRED")
								{
									Bread *thing = new Bread();
									thing->set_name(entdata[0]);
									try
									{
										temp_entities[entdata[2]]->add(entdata[0], thing);
									}
									catch (const std::invalid_argument&)
									{
									}
								}
							}
						}
					}
				}
				Adventures::instance().addAdventure(adventurenum, adventure);
				adventurenum++;
			}
		}
	}
}

void testcomposites()
{
	Container c1 = Container();
	c1.set_name("c1");
	Container *c2 = new Container();
	c2->set_name("c2");
	Container *c3 = new Container();
	c3->set_name("c3");
	Item *i1 = new Item();
	i1->set_name("i1");
	Item *i2 = new Item();
	i2->set_name("i2");
	Item *i3 = new Item();
	i3->set_name("i3");
	Item *i4 = new Item();
	i4->set_name("i4");
	c1.add("i1", i1);
	c2->add("i2", i2);
	c2->add("i3", i3);
	c3->add("i4", i4);
	c1.add("c2", c2);
	c1.add("c3", c3);
	c1.action(Action::OPEN, "");
}

int main()
{
	//testcomposites();
	//return 0;

	Adventures::instance();
	StateManager gameStateManager = StateManager();

	loadAvdentures();

	while (gameStateManager.gameIsActive())
	{
		gameStateManager.update();
	}

	cout << "Goodbye! Thanks for playing!";

	return 0;
}