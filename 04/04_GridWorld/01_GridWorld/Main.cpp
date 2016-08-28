#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <conio.h>
#include <deque>

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
vector<char> validMoves = vector<char>();
deque<char> moveQueue = deque<char>();

string deathStrings[5] = {
	"You fell down a hole. Game over!",
	"You were crushed by a cave in. Game over!",
	"You suffocated by your own fart. Game over!",
	"You were eaten by a bear. Game over!",
	"You were killed by an evil rabbit. Game over!"
};

bool shouldRender = true;

void input()
{
	if (_kbhit() != 0)
	{
		bool valid = false;
		string input = "";
		char tempMove;
		getline(std::cin, input);
		tempMove = toupper(input.at(0));

		//Check for exit
		if (tempMove == 'Q')
		{
			moveQueue.push_back(tempMove);
			state = 3;
			valid = true;
		}
		
		//Validate move
		for each (char direction in validMoves)
		{
			if (direction == tempMove)
			{
				moveQueue.push_back(tempMove);
				valid = true;
				break;
			}
		}

		if (!valid) cout << "Enter direction to move: ";
	}
}

void update()
{
	if (state == 0 && moveQueue.size() > 0)
	{
		//Move position in correct direction
		switch (moveQueue.at(0))
		{
		case 'N':
			gameMap[yPos][xPos] = ' ';
			yPos = yPos - 1;
			break;
		case 'S':
			gameMap[yPos][xPos] = ' ';
			yPos = yPos + 1;
			break;
		case 'E':
			gameMap[yPos][xPos] = ' ';
			xPos = xPos + 1;
			break;
		case 'W':
			gameMap[yPos][xPos] = ' ';
			xPos = xPos - 1;
			break;
		default:
			break;
		}
		moveQueue.pop_front();

		//Check new position
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

		if (gameMap[7][2] == ' ') gameMap[7][2] = '#';

		//Get valid moves for next move
		validMoves.clear();
		if (gameMap[yPos - 1][xPos] != '#') validMoves.push_back('N');
		if (gameMap[yPos + 1][xPos] != '#') validMoves.push_back('S');
		if (gameMap[yPos][xPos + 1] != '#') validMoves.push_back('E');
		if (gameMap[yPos][xPos - 1] != '#') validMoves.push_back('W');

		shouldRender = true;
	}	
}

void render()
{
	if (state == 0 && shouldRender)
	{
		cout << "Current map" << endl;
		//Print current map
		for (int i = 0; i < mapSize; i++)
		{
			for (int j = 0; j < mapSize; j++)
			{
				cout << gameMap[i][j] << " ";
			}
			cout << endl;
		}

		//Print valid moves
		string moveMessage = "Valid Moves: ";
		for each (char direction in validMoves)
		{
			moveMessage = moveMessage + direction + ", ";
		}
		cout << moveMessage << endl;
		cout << "Enter direction to move: ";

		shouldRender = false;
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

	validMoves.push_back('N');

	render();

	while (state == 0)
	{
		input();
		update();
		render();
	}

	//final cin for testing only
	char blah;
	cin >> blah;

	return 0;
}