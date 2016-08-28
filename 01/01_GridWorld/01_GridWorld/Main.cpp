#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

int const SIZE = 8;

//0 - playing, 1 - win, 2 - death, 3 - quit
int state = 0;

string deathStrings[5] = {
	"You fell down a hole. Game over!",
	"You were crushed by a cave in. Game over!",
	"You suffocated by your own fart. Game over!",
	"You were eaten by a bear. Game over!",
	"You were killed by an evil rabbit. Game over!"
};

char theMove;

class Player
{
public:
	Player();
	int xPos();
	int yPos();
	void setX(int newXPos);
	void setY(int newYPos);
private:
	int _xPos;
	int _yPos;
};

Player::Player()
{
	_xPos = 2;
	_yPos = 7;
}
int Player::xPos()
{
	return _xPos;
}
int Player::yPos()
{
	return _yPos;
}
void Player::setX(int newXPos)
{
	_xPos = newXPos;
}
void Player::setY(int newYPos)
{
	_yPos = newYPos;
}

class Map
{
public:
	Map();
	void movePlayer(char direction);
	void checkPlayerState();
	vector<char> getValidMoves();
	void renderMap();
private:
	Player player;
	char gameMap[SIZE + 1][SIZE] = {
		{ '#','#','#','#','#','#','#','#' },
		{ '#','G',' ','D','#','D',' ','#' },
		{ '#',' ',' ',' ','#',' ',' ','#' },
		{ '#','#','#',' ','#',' ','D','#' },
		{ '#',' ',' ',' ','#',' ',' ','#' },
		{ '#',' ','#','#','#','#',' ','#' },
		{ '#',' ',' ',' ',' ',' ',' ','#' },
		{ '#','#','S','#','#','#','#','#' },
		{ '#','#','#','#','#','#','#','#' }
	};
};

Map::Map()
{
	player = Player();
}
void Map::movePlayer(char direction)
{
	switch (direction)
	{
	case 'N':
		gameMap[player.yPos()][player.xPos()] = ' ';
		player.setY(player.yPos() - 1);
		break;
	case 'S':
		gameMap[player.yPos()][player.xPos()] = ' ';
		player.setY(player.yPos() + 1);
		break;
	case 'E':
		gameMap[player.yPos()][player.xPos()] = ' ';
		player.setX(player.xPos() + 1);
		break;
	case 'W':
		gameMap[player.yPos()][player.xPos()] = ' ';
		player.setX(player.xPos() - 1);
		break;
	default:
		break;
	}
}
void Map::checkPlayerState()
{
	switch (gameMap[player.yPos()][player.xPos()])
	{
	case 'D':
		state = 2;
		break;
	case 'G':
		state = 1;
		break;
	case ' ':
		gameMap[player.yPos()][player.xPos()] = 'P';
		break;
	}
	if (gameMap[7][2] == ' ') gameMap[7][2] = '#';
}
vector<char> Map::getValidMoves()
{
	vector<char> moves;
	moves.clear();
	if (gameMap[player.yPos() - 1][player.xPos()] != '#') moves.push_back('N');
	if (gameMap[player.yPos() + 1][player.xPos()] != '#') moves.push_back('S');
	if (gameMap[player.yPos()][player.xPos() + 1] != '#') moves.push_back('E');
	if (gameMap[player.yPos()][player.xPos() - 1] != '#') moves.push_back('W');
	return moves;
}
void Map::renderMap()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << gameMap[i][j] << " ";
		}
		cout << endl;
	}
}

Map theMap;

void input()
{
	//Get and print valid moves
	vector<char> validMoves = theMap.getValidMoves();
	string moveMessage = "Valid Moves: ";
	for each (char direction in validMoves)
	{
		moveMessage = moveMessage + direction + ", ";
	}
	cout << moveMessage << endl;

	//Accept input
	bool invalid = true;
	do
	{
		string input = "";
		cout << "Enter direction to move: ";
		cin >> input;
		theMove = toupper(input.at(0));

		//Check for exit
		if (theMove == 'Q')
		{
			state = 3;
			invalid = false;
			break;
		}

		//Validate move
		for each (char direction in validMoves)
		{
			if (direction == theMove)
			{
				invalid = false;
				break;
			}
		}
	} while (invalid);
}

void update()
{
	if (state == 0)
	{
		theMap.movePlayer(theMove);
		theMap.checkPlayerState();
	}	
}

void render()
{
	if (state == 0)
	{
		cout << "Current map" << endl;
		theMap.renderMap();
	}
	else if (state == 1)
	{
		cout << "Congratulations! You reached the chest of Gold!" << endl;
	}
	else if (state == 2)
	{
		int death = rand() % 5;
		cout << deathStrings[death] << endl;
	}
	else if (state == 3)
	{
		cout << "Thanks for playing. Goodbye!" << endl;
	}
	
}

int main()
{
	cout << "Welcome to GridWorld! By Ford Killeen 9731822" << endl;
	cout << "You may use N, S, E, W to navigate the world and Q to quit." << endl;

	render();

	while (state == 0)
	{
		input();
		update();
		render();
	}

	char blah;
	cin >> blah;

	return 0;
}