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
			bool firstline = true;
			string line;
			std::ifstream file;
			file.open(advfile);
			if (file.is_open())
			{
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
					}
				}
				Adventures::instance().addAdventure(adventurenum, adventure);
				adventurenum++;
			}
		}
	}
}

int main()
{
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