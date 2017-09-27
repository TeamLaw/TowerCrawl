
#include "TowerCrawl.h"

//Save game to file?

int main()
{
	delCounter = 0;
	difficulty = 0;
	location = 1;
	clock_t startTime = clock();
	srand((unsigned)time(&t));

	createPlayer();
	createFloor();
	createNPCs();

	while (1)
	{
		if ((double)(clock() - startTime) > 1000)
		{
			if (player.roomLoc->enemy.health > 0) { enemyMove(); }
			startTime = clock();
		}
		if (_kbhit()) { playerMove(); }

		if (checkInteraction() == -1) { return; }
	}
	clearMemory();
	
	return 0;
}

int coordCompare(COORD coord1, COORD coord2)//OVERLOAD OPERATORS IN C++!!!
{
	return (coord1.X == coord2.X && coord1.Y == coord2.Y);
}

void moveCursor(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x, y });
}

/*randomNum(int low, int high) generates a random number
Parameters: 
	low - The lowest possible random number 
	high- The highest possible random number
Returns: 
	the random number
*/
int randomNum(int low, int high)
{
	int r;

	r = rand() % (high - low) + low;
	return r;
}


int minCheck(int mod)
{//Compares how many rooms have been entered with how many are left, if all have been entered, spawn boss or continue spawning rooms
	int counter = mod;
  
	for (int i = 0; i < delCounter; i++) { counter += delPointers[i]->entered; }
	
	return (counter == delCounter);
}

void clearMemory()
{
	for (int i = 0; i < delCounter; i++)
		free(delPointers[i]);
	delCounter = 0;
}