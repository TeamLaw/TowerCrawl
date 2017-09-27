/*Game.c
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
*/
#include "TowerCrawl.h"

//Save game to file?

int main()
{
	delCounter = 0;
	difficulty = 0;
	clock_t startTime = clock();
	srand((unsigned)time(&t));

	// display greeting
	printGameIntroMessage();

	createPlayer();
	createFloor();

	while (1)
	{
		if ((double)(clock() - startTime) > 1000)
		{
			enemyMove();
			startTime = clock();
		}
		if (_kbhit()) { playerMove(); }

		if (checkInteraction() == -1) { return; }

	}
	clearMemory();

	return 0;
}

/*
randomNum(int low, int high) generates a random number
Parameters:
low - The lowest possible random number
high- The highest possible random number
Returns:
the random number
*/
int coordCompare(COORD coord1, COORD coord2)//OVERLOAD OPERATORS IN C++!!!
{
	return (coord1.X == coord2.X && coord1.Y == coord2.Y);
}

/*
randomNum(int low, int high) generates a random number
Parameters:
low - The lowest possible random number
high- The highest possible random number
Returns:
the random number
*/
void moveCursor(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x, y });
}

/*
randomNum(int low, int high) generates a random number
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

/*
randomNum(int mod) Compares how many rooms have been entered with how many are left, if all have been entered, spawn boss or continue spawning rooms
Parameters:
mod - edits it behavior
Returns:

Programmer: Law
*/
int minCheck(int mod)
{
	int counter = mod;

	for (int i = 0; i < delCounter; i++) { counter += delPointers[i]->entered; }

	return (counter == delCounter);
}

/*
clearMemory() At the end of the program, this function frees up all the memory
Parameters:
None
Returns:
Void
Programmer: Law
*/
void clearMemory()
{
	for (int i = 0; i < delCounter; i++)
		free(delPointers[i]);
	delCounter = 0;
}

/*
printGameIntroMessage() Handles the intro message and art
Parameters:
None
Returns:
Void
Programmer: Law
*/
void printGameIntroMessage()
{
	printf("TO ADD GRAPHIC\nPRESS ANY KEY TO START THE GAME \n");
	printf("> ");
	_getch();
	system("cls");

	printf("~ An evil wizard has stolen your crown. ~\n~ You and your finest warriors travel to the wizard's tower ~\n~ to take it back! ~ \n>");
	_getch();
	system("cls");

	printf("~ You burst down the front door of his tower. ~\n~ The room goes dark and you find yourself alone, ~\n~ in a strange room.... ~ \n>");
	_getch();
	system("cls");

	printf("~ Doors appear on the walls. The wizard strange ~\n~ magic will not... cannot keep you from your goal. Travel to the ~\n~ top of the tower and end this maddness! ~ \n>");
	_getch();
	system("cls");

}