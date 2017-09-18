#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

//Save game to file?
int checkPlayerPos(int, int);
void drawRoom();
void drawHealth();
void playerMove();
void createEnemies(struct Room *);
void createPlayer();
void createRooms();
void enemyMove();
void drawEntities(int, int, struct Entity *);
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
	int damage;//attack power
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
	drawEntities(0, 0, &newPlayer);
	drawEntities(0, 0, &tower.floors[0].rooms[newPlayer.row][newPlayer.col].enemy);

	while (1)
	{
		if ((double)(clock() - startTime) > 1000)
		{
			enemyMove();
			startTime = clock();
		}
		if (_kbhit()) { playerMove(); }
	}
	
	return 0;
}
	
void drawEntities(int oldX, int oldY, struct Entity * entity)//send entity to redraw, not xy
{
	moveCursor((*(entity)).x, (*(entity)).y);

	printf("%c", (*(entity)).marker);
	
	if (oldX || oldY)
	{
		moveCursor(oldX, oldY);
		printf(" ");
	}

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
	newPlayer.x = 5;
	newPlayer.y = 5;
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
				(*(room_ptr)).xSize = 25;
				(*(room_ptr)).ySize = 25;
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
	int x = (*(room_ptr)).enemy.x, y = (*(room_ptr)).enemy.y;

	if (abs((*(room_ptr)).enemy.x - newPlayer.x) > abs((*(room_ptr)).enemy.y - newPlayer.y))
	{
		(*(room_ptr)).enemy.x += ((*(room_ptr)).enemy.x < newPlayer.x ? 1 : -1);
	}
	else 
	{ 
		(*(room_ptr)).enemy.y += ((*(room_ptr)).enemy.y < newPlayer.y ? 1 : -1);
	}
	drawEntities(x, y, &(*(room_ptr)).enemy);
}

void playerMove()
{
	int x = newPlayer.x, y = newPlayer.y;
	struct Room room = tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	switch (getch())
	{//Need to check for collision with other entities
	case 'w':
		if (checkPlayerPos(1, -1));
		else if (newPlayer.y > 1) { 
			newPlayer.y--;
			drawEntities(x, y, &newPlayer);
		}
		break;
	case 'a':
		if (checkPlayerPos(2, -1));
		else if (newPlayer.x > 1) { 
			newPlayer.x--; 
			drawEntities(x, y, &newPlayer);
		}
		break;
	case 's':
		if (checkPlayerPos(3, 1));
		else if (newPlayer.y < (room.ySize - 2)) { 
			newPlayer.y++; 
			drawEntities(x, y, &newPlayer);
		}
		break;
	case 'd':
		if (checkPlayerPos(4, 1));
		else if (newPlayer.x < (room.xSize - 2)) { 
			newPlayer.x++; 
			drawEntities(x, y, &newPlayer);
		}
		break;
	}
}

int checkPlayerPos(int direction, int newPos)
{
	struct Room room = tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	switch (direction)
	{
	case 1:
		if (room.nDoor)
		{
			if (newPlayer.y == 1 && newPlayer.x == (room.xSize / 2))
			{
				newPlayer.y = abs(1 - (room.ySize - 1));
				newPlayer.row += newPos;
				drawRoom();
				drawHealth();
				drawEntities(0, 0, &newPlayer);
				drawEntities(0, 0, &tower.floors[0].rooms[newPlayer.row][newPlayer.col].enemy);
				return 1;
			}
		}
		break;
	case 2:
		if (room.wDoor)
		{
			if (newPlayer.x == 1 && newPlayer.y == (room.ySize / 2))
			{
				newPlayer.x = abs(1 - (room.xSize - 1));
				newPlayer.col += newPos;
				drawRoom();
				drawHealth();
				drawEntities(0, 0, &newPlayer);
				drawEntities(0, 0, &tower.floors[0].rooms[newPlayer.row][newPlayer.col].enemy);
				return 1;
			}
		}
		break;
	case 3:
		if (room.sDoor)
		{
			if (newPlayer.y == room.ySize - 2 && newPlayer.x == (room.xSize / 2))
			{
				newPlayer.y = abs(newPlayer.y - (room.ySize - 1));
				newPlayer.row += newPos;
				drawRoom();
				drawHealth();
				drawEntities(0, 0, &newPlayer);
				drawEntities(0, 0, &tower.floors[0].rooms[newPlayer.row][newPlayer.col].enemy);
				return 1;
			}
		}
		break;
	case 4:
		if (room.eDoor)
		{
			if (newPlayer.x == room.xSize - 2 && newPlayer.y == (room.ySize / 2))
			{
				newPlayer.x = abs(newPlayer.x - (room.xSize - 1));
				newPlayer.col += newPos;
				drawRoom();
				drawHealth();
				drawEntities(0, 0, &newPlayer);
				drawEntities(0, 0, &tower.floors[0].rooms[newPlayer.row][newPlayer.col].enemy);
				return 1;
			}
		}
		break;
	}
	return 0;
}

void drawRoom()
{//Door coded for 2 slots at halfway point of wall
	struct Room room = tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	system("cls");
	for (int n = 0; n < room.xSize; n++) 
	{ 
		if ((n == (room.xSize / 2)) && room.nDoor) { printf(" "); }
		else { printf("="); }
	}
	printf("\n");
	for (int y = 0; y < room.ySize - 2; y++)
	{
		if ((y == (room.ySize / 2 - 1)) && room.wDoor) { printf(" "); }
		else { printf("["); }
		for (int x = 0; x < room.xSize - 2; x++) { printf(" "); }
		if ((y == (room.ySize / 2 - 1)) && room.eDoor) { printf(" \n"); }
		else { printf("]\n"); }
	}
	for (int s = 0; s < room.xSize; s++) 
	{ 
		if ((s == (room.xSize / 2)) && room.sDoor) { printf(" "); }
		else { printf("="); }
	}
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