
#include "TowerCrawl.h"

//Save game to file?

int main()
{
	delCounter = 0;
	branch = 50;
	difficulty = 0;
	clock_t startTime = clock();
	srand((unsigned)time(&t));
	COORD coord = { 0, 0 };

	// display greeting
	printGameIntroMessage();

	createPlayer();
	player.roomLoc = createRoom();
	player.coord.X = player.roomLoc->xSize / 2;
	player.coord.Y = player.roomLoc->ySize / 2;
	openDoors(player.roomLoc);
	
	drawRoom(player.roomLoc);
	drawInfo();
	drawEntities(coord, player.coord, player.marker);

	while (1)
	{
		if ((double)(clock() - startTime) > 1000)
		{
			enemyMove();
			startTime = clock();
		}
		if (_kbhit()) { playerMove(); }

		if (checkInteraction() == -1)
		{
			return ; 
		}
	}
	for (int i = 0; i < delCounter; i++)
		free(delPointers[i]);
	
	return 0;
}

int coordCompare(COORD coord1, COORD coord2)//OVERLOAD OPERATORS IN C++!!!
{
	return (coord1.X == coord2.X && coord1.Y == coord2.Y);
}

void moveCursor(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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


int minCheck()
{//Compares how many rooms have been entered with how many are left, if all have been entered, spawn boss or continue spawning rooms
	int counter = 0;
  
	for (int i = 0; i < delCounter; i++) { counter += delPointers[i]->entered; }
	
	return (counter == delCounter);
}

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