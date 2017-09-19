#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include "TowerCrawl.h"

//Save game to file?

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
	
void drawEntities(int oldX, int oldY, struct Entity * entity)
{
	moveCursor(entity->coord.X, entity->coord.Y);

	printf("%c", entity->marker);
	
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
	newPlayer.coord.X = 5;
	newPlayer.coord.Y = 5;
	newPlayer.maxHealth = 10;
	newPlayer.health = 10;
}

void createRooms()
{//hardcoded 3x3 floor setup to place doors and room size
	int boss = 1, counter = 0, randomN = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			struct Room * room_ptr = &tower.floors[0].rooms[i][j];
			if (room_ptr)
			{
				room_ptr->nDoor = (i != 0 ? 1 : 0);
				room_ptr->sDoor = (i != 2 ? 1 : 0);
				room_ptr->eDoor = (j != 2 ? 1 : 0);
				room_ptr->wDoor = (j != 0 ? 1 : 0);
				room_ptr->xSize = 25;
				room_ptr->ySize = 25;
				randomN = randomNum(counter, 9);
				createEntities(room_ptr, (randomN == 8 ? boss : 0));
				boss -= (boss && randomN == 8 ? 1 : 0);
				counter++;
			}
		}
	}
}

int randomNum(int low, int high)
{
	int r;
	time_t t;

	srand((unsigned)time(&t));

	r = rand() % (high - low) + low;
	return r;
}

void createEntities(struct Room * room_ptr, int type)
{//hardcoded enemy limit per floor and enemy stats and location
	if (!room_ptr->enemy.maxHealth)
	{
		room_ptr->enemy.marker = (type ? '#' : 'x');
		room_ptr->enemy.coord.X = 9;
		room_ptr->enemy.coord.Y = 9;
		room_ptr->enemy.health = 2 * (type ? 5 : 2);
		room_ptr->enemy.maxHealth = 2 * (type ? 5 : 2);
		room_ptr->enemy.damage = 1 * (type ? 3 : 1);
		room_ptr->enemy.typeCheck = type;
	}
}

void enemyMove()
{
	struct Entity * enemy_ptr = &tower.floors[0].rooms[newPlayer.row][newPlayer.col].enemy;
	int x = enemy_ptr->coord.X, y = enemy_ptr->coord.Y;

	if (abs(enemy_ptr->coord.X - newPlayer.coord.X) > abs(enemy_ptr->coord.Y - newPlayer.coord.Y))
	{
		enemy_ptr->coord.X += (enemy_ptr->coord.X < newPlayer.coord.X ? 1 : -1);
	}
	else 
	{ 
		enemy_ptr->coord.Y += (enemy_ptr->coord.Y < newPlayer.coord.Y ? 1 : -1);
	}
	drawEntities(x, y, enemy_ptr);
}

void playerMove()
{
	int x = newPlayer.coord.X, y = newPlayer.coord.Y;
	struct Room room = tower.floors[0].rooms[newPlayer.row][newPlayer.col];

	switch (getch())
	{
	case 'w':
		if (checkPlayerPos(1, -1));
		else if (newPlayer.coord.Y > 1) { 
			newPlayer.coord.Y--;
			drawEntities(x, y, &newPlayer);
		}
		break;
	case 'a':
		if (checkPlayerPos(2, -1));
		else if (newPlayer.coord.X > 1) { 
			newPlayer.coord.X--; 
			drawEntities(x, y, &newPlayer);
		}
		break;
	case 's':
		if (checkPlayerPos(3, 1));
		else if (newPlayer.coord.Y < (room.ySize - 2)) { 
			newPlayer.coord.Y++; 
			drawEntities(x, y, &newPlayer);
		}
		break;
	case 'd':
		if (checkPlayerPos(4, 1));
		else if (newPlayer.coord.X < (room.xSize - 2)) { 
			newPlayer.coord.X++; 
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
			if (newPlayer.coord.Y == 1 && newPlayer.coord.X == (room.xSize / 2))
			{
				newPlayer.coord.Y = abs(1 - (room.ySize - 1));
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
			if (newPlayer.coord.X == 1 && newPlayer.coord.Y == (room.ySize / 2))
			{
				newPlayer.coord.X = abs(1 - (room.xSize - 1));
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
			if (newPlayer.coord.Y == room.ySize - 2 && newPlayer.coord.X == (room.xSize / 2))
			{
				newPlayer.coord.Y = abs(newPlayer.coord.Y - (room.ySize - 1));
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
			if (newPlayer.coord.X == room.xSize - 2 && newPlayer.coord.Y == (room.ySize / 2))
			{
				newPlayer.coord.X = abs(newPlayer.coord.X - (room.xSize - 1));
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