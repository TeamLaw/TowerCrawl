#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "TowerCrawl.h"

//Save game to file?
int checkPlayerPos(int, int, int, int);
void drawRoom();
void drawHealth();
void playerMove();
void createEnemies(struct Room *);
void createPlayer();
void createRooms();
char checkEntities(int, int, struct Room);
void enemyMove();
void reDraw(int, int, struct Entity *);
void moveCursor(int, int);

struct Entity 
{
	char marker;
	int x;//Horizontal location in room
	int y;//Vertical location in room
	int row;//Horizontal location on floor
	int col;//Vertical location on floor
	int floorLoc;//Floor location in tower
	int health;//Current health
	int maxHealth;//Max health
};

struct Room 
{//One enemy per room
	int xSize;
	int ySize;
    int nDoor;
	int sDoor;
	int eDoor;
	int wDoor;
	struct Entity enemy;
};

struct Floor 
{//Hardcoded 3x3 rooms for the floor
	struct Room rooms[3][3];
};

struct Tower
{//Hardcoded 7 floors
	struct Floor floors[7];
};

struct Entity newPlayer;
struct Tower tower;

int main()
{
	clock_t startTime = clock();

	createPlayer();
	createRooms();
	drawRoom();
	drawHealth();

	while (1)
	{
		if ((double)(clock() - startTime) > 100)
		{
			if ((double)(clock() - startTime) > 2000)
			{
				enemyMove();
				startTime = clock();
			}
			if (_kbhit()) { playerMove(); }
		}
	}
	
	return 0;
}
	
void reDraw(int oldX, int oldY, struct Entity * entity)//send entity to redraw, not xy
{
	moveCursor((*(entity)).x, (*(entity)).y);

	printf("%c", (*(entity)).marker);

	moveCursor(oldX, oldY);
	printf(" ");

	moveCursor(0, 0);
}

void moveCursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void createPlayer()
{//hardcoded player info
	newPlayer.marker = 'o';
	newPlayer.row = 0;
	newPlayer.col = 0;
	newPlayer.floorLoc = 0;
	newPlayer.x = 4;
	newPlayer.y = 4;
	newPlayer.maxHealth = 10;
	newPlayer.health = 10;
}

void createRooms()
{//hardcoded 3x3 floor setup to place doors and room size
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			struct Room * room_ptr = &tower.floors[0].rooms[i][j];
			if (room_ptr)
			{
				(*(room_ptr)).nDoor = (i != 0 ? 1 : 0);
				(*(room_ptr)).sDoor = (i != 2 ? 1 : 0);
				(*(room_ptr)).eDoor = (j != 2 ? 1 : 0);
				(*(room_ptr)).wDoor = (j != 0 ? 1 : 0);
				(*(room_ptr)).xSize = 16;
				(*(room_ptr)).ySize = 16;
				createEnemies(room_ptr);
			}
		}
	}
}

void createEnemies(struct Room * room_ptr)
{//hardcoded enemy limit per floor and enemy stats and location
	if (!(*(room_ptr)).enemy.maxHealth)
	{
		(*(room_ptr)).enemy.marker = 'x';
		(*(room_ptr)).enemy.x = 9;
		(*(room_ptr)).enemy.y = 9;
		(*(room_ptr)).enemy.floorLoc = newPlayer.floorLoc;
		(*(room_ptr)).enemy.health = 5;
		(*(room_ptr)).enemy.maxHealth = 5;
	}
}

void enemyMove()
{
	struct Room * room_ptr = &tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	if (abs((*(room_ptr)).enemy.x - newPlayer.x) > abs((*(room_ptr)).enemy.y - newPlayer.y))
	{
		(*(room_ptr)).enemy.x += ((*(room_ptr)).enemy.x < newPlayer.x ? 1 : -1);
	}
	else 
	{ 
		(*(room_ptr)).enemy.y += ((*(room_ptr)).enemy.y < newPlayer.y ? 1 : -1);
	}
}

void playerMove()
{
	int x = newPlayer.x, y = newPlayer.y;
	struct Room room = tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	switch (getch())
	{//Need to check for collision with other entities
	case 'w':
		if (checkPlayerPos(room.nDoor, 0, -1, room.ySize));
		else if (newPlayer.y > 0) { newPlayer.y--; }
		break;
	case 'a':
		if (checkPlayerPos(room.wDoor, 0, -1, room.xSize));
		else if (newPlayer.x > 0) { newPlayer.x--; }
		break;
	case 's':
		if (checkPlayerPos(room.sDoor, room.ySize - 3, 1, room.ySize));
		else if (newPlayer.y < (room.ySize - 3)) { newPlayer.y++; }
		break;
	case 'd':
		if (checkPlayerPos(room.eDoor, room.xSize - 3, 1, room.xSize));
		else if (newPlayer.x < (room.xSize - 3)) { newPlayer.x++; }
		break;
	}
	reDraw(x, y, &newPlayer);
}

int checkPlayerPos(int doorCheck, int locCheck, int newPos, int size)
{//Needs to be re-written, bug with entering doors when hugging walls
	if (doorCheck)
	{
		if (newPlayer.x == locCheck && (newPlayer.y == (size / 2) || newPlayer.y == (size / 2 - 1)))
		{
			newPlayer.x = abs(locCheck - (size - 3));
			newPlayer.col += newPos;
			return 1;
		}
		else if (newPlayer.y == locCheck && (newPlayer.x == (size / 2) || newPlayer.x == (size / 2 - 1)))
		{
			newPlayer.y = abs(locCheck - (size - 3));
			newPlayer.row += newPos;
			return 1;
		}
	}

	return 0;
}

void drawRoom()
{//Door coded for 2 slots at halfway point of wall
	struct Room room = tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	for (int n = 0; n < room.xSize; n++) 
	{ 
		if ((n == (room.xSize / 2) || n == (room.xSize / 2 - 1)) && room.nDoor) { printf(" "); }
		else { printf("="); }
	}
	printf("\n");
	for (int y = 0; y < room.ySize - 2; y++)
	{
		if ((y == (room.ySize / 2) || y == (room.ySize / 2 - 1)) && room.wDoor) { printf(" "); }
		else { printf("["); }
		for (int x = 0; x < room.xSize - 2; x++) 
		{ 
		    printf("%c", checkEntities(x, y, room));
		}
		if ((y == (room.ySize / 2) || y == (room.ySize / 2 - 1)) && room.eDoor) { printf(" \n"); }
		else { printf("]\n"); }
	}
	for (int s = 0; s < room.xSize; s++) 
	{ 
		if ((s == (room.xSize / 2) || s == (room.xSize / 2 - 1)) && room.sDoor) { printf(" "); }
		else { printf("="); }
	}
}

char checkEntities(int x, int y, struct Room room)
{
	if (room.enemy.maxHealth && room.enemy.health > 0 && room.enemy.x == x && room.enemy.y == y) { return 120; }
	else if (y == newPlayer.y && x == newPlayer.x) { return 111; }
	else { return 32; }
}

void drawHealth()
{
	printf("\n\n\n");
	printf("HP: ");
	for (int i = 0; i < newPlayer.maxHealth; i++)
	{
		printf("%c", (newPlayer.health > i ? 47 : 46));
	}
	printf("  %d/%d", newPlayer.health, newPlayer.maxHealth);
}