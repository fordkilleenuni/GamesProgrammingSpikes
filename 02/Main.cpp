#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

int state = 0;
//0 - playing, 1 - win, 2 - death, 3 - quit

int const mapSize = 8;

char gameMap[mapSize+1][mapSize] = {
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

int xPos = 2;
int yPos = 7;

string deathStrings[5] = {
	"You fell down a hole. Game over!",
	"You were crushed by a cave in. Game over!",
	"You suffocated by your own fart. Game over!",
	"You were eaten by a bear. Game over!",
	"You were killed by an evil rabbit. Game over!"
};

char theMove;

void input()
{
	//Get valid moves
	std::vector<char> validMoves;
	if (gameMap[yPos - 1][xPos] != '#') validMoves.push_back('N');
	if (gameMap[yPos + 1][xPos] != '#') validMoves.push_back('S');
	if (gameMap[yPos][xPos + 1] != '#') validMoves.push_back('E');
	if (gameMap[yPos][xPos - 1] != '#') validMoves.push_back('W');

	string moveMessage = "Valid Moves: ";
	for each (char direction in validMoves)
	{
		moveMessage = moveMessage + direction + ", ";
	}

	//Print valid moves
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
		switch (theMove)
		{
		case 'N':
			gameMap[yPos][xPos] = ' ';
			yPos = yPos - 1;
			switch (gameMap[yPos][xPos])
			{
			case 'D':
				state = 2;
				break;
			case 'G':
				state = 1;
				break;
			case ' ':
				gameMap[yPos][xPos] = 'P';
				break;
			}
			break;
		case 'S':
			gameMap[yPos][xPos] = ' ';
			yPos = yPos + 1;
			switch (gameMap[yPos][xPos])
			{
			case 'D':
				state = 2;
				break;
			case 'G':
				state = 1;
				break;
			case ' ':
				gameMap[yPos][xPos] = 'P';
				break;
			}
			break;
		case 'E':
			gameMap[yPos][xPos] = ' ';
			xPos = xPos + 1;
			switch (gameMap[yPos][xPos])
			{
			case 'D':
				state = 2;
				break;
			case 'G':
				state = 1;
				break;
			case ' ':
				gameMap[yPos][xPos] = 'P';
				break;
			}
			break;
		case 'W':
			gameMap[yPos][xPos] = ' ';
			xPos = xPos - 1;
			switch (gameMap[yPos][xPos])
			{
			case 'D':
				state = 2;
				break;
			case 'G':
				state = 1;
				break;
			case ' ':
				gameMap[yPos][xPos] = 'P';
				break;
			}
			break;
		default:
			break;
		}

		if (gameMap[7][2] == ' ') gameMap[7][2] = '#';
	}	
}

void render()
{
	if (state == 0)
	{
		cout << "Current map" << endl;

		for (int i = 0; i < mapSize; i++)
		{
			for (int j = 0; j < mapSize; j++)
			{
				cout << gameMap[i][j] << " ";
			}
			cout << endl;
		}
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