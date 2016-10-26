#include <stdio.h>
#include <iostream>
#include "StateManager.h"
#include "Player.h"

using namespace std;

int main()
{
	StateManager gameStateManager = StateManager();

	while (gameStateManager.gameIsActive())
	{
		gameStateManager.update();
	}

	cout << "Goodbye! Thanks for playing!";

	return 0;
}