
#include "TowerCrawl.h"

//Save game to file?

struct Player newPlayer;
struct Tower tower;
time_t t;

int main()
{
	int difficulty = 0;
	clock_t startTime = clock();
	srand((unsigned)time(&t));
	COORD coord = { 0, 0 };

	createPlayer(&newPlayer);
	createTower(&tower, difficulty);
	drawRoom();
	drawInfo();
	drawEntities(coord, newPlayer.coord, newPlayer.marker);

	while (1)
	{
		if ((double)(clock() - startTime) > 1000)
		{
			enemyMove();
			startTime = clock();
		}
		if (_kbhit()) { playerMove(); }
		checkInteraction();
	}
	
	return 0;
}

void checkInteraction()
{
	int interactionResult = 0;

	struct Room * room = &tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];
	struct Enemy * enemy = &room->enemy;
	COORD coord = { 0, 0 };
	
	if (newPlayer.coord.X == enemy->coord.X && newPlayer.coord.Y == enemy->coord.Y)
	{
		interactionResult = handleEncounter(&newPlayer, enemy);
		if (!interactionResult)
		{
			newPlayer.coord.X += (newPlayer.coord.X <= room->xSize / 2 ? (room->xSize / 3) : -(room->xSize / 3));
			newPlayer.coord.Y += (newPlayer.coord.Y <= room->ySize / 2 ? (room->ySize / 3) : -(room->ySize / 3));
			drawRoom();
			drawInfo();
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
			if (room->isPortal) { drawEntities(coord, room->portal.coord, room->portal.marker); }
		}
		else if (interactionResult == 1 && enemy->isBoss == 1)
		{
			room->isPortal = 1;
			if (newPlayer.coord.X == room->xSize / 2 && newPlayer.coord.Y == room->ySize / 2) { newPlayer.coord.Y -= 2; }
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
			drawEntities(coord, room->portal.coord, room->portal.marker);
		}
		else if (interactionResult == -1)
		{
			//You ded
		}
	}
}
	
void drawEntities(COORD oldCoord, COORD coord, char marker)
{
	moveCursor(coord.X, coord.Y);

	printf("%c", marker);
	
	if (oldCoord.X || oldCoord.Y)
	{
		moveCursor(oldCoord.X, oldCoord.Y);
		printf(" ");
	}

	moveCursor(0, 0);
}

void moveCursor(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int randomNum(int low, int high)
{
	int r;

	r = rand() % (high - low) + low;
	return r;
}

void enemyMove()
{
	struct Enemy * enemy_ptr = &tower.floors[0].rooms[newPlayer.pos].enemy;
	COORD coord = { enemy_ptr->coord.X, enemy_ptr->coord.Y };

	if (abs(enemy_ptr->coord.X - newPlayer.coord.X) > abs(enemy_ptr->coord.Y - newPlayer.coord.Y))
	{
		enemy_ptr->coord.X += (enemy_ptr->coord.X < newPlayer.coord.X ? 1 : -1);
	}
	else { enemy_ptr->coord.Y += (enemy_ptr->coord.Y < newPlayer.coord.Y ? 1 : -1); }
	
	if (enemy_ptr->maxHealth) { drawEntities(coord, enemy_ptr->coord, enemy_ptr->marker); }
}

void playerMove()
{
	COORD coord = newPlayer.coord;
	struct Room room = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];

	switch (getch())
	{
	case 'w':
		if (checkPlayerPos(1));
		else if (newPlayer.coord.Y > 1) 
		{ 
			newPlayer.coord.Y--;
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
		}
		break;
	case 's':
		if (checkPlayerPos(2));
		else if (newPlayer.coord.Y < (room.ySize - 2))
		{
			newPlayer.coord.Y++;
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
		}
		break;
	case 'a':
		if (checkPlayerPos(3));
		else if (newPlayer.coord.X > 1) 
		{ 
			newPlayer.coord.X--; 
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
		}
		break;
	case 'd':
		if (checkPlayerPos(4));
		else if (newPlayer.coord.X < (room.xSize - 2)) 
		{ 
			newPlayer.coord.X++; 
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
		}
		break;
	}
}

int checkPlayerPos(int direction)
{
	struct Room room = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];
	struct Enemy enemy;
	COORD coord = { 0, 0 };

	switch (direction)
	{
	case 1:
		if (room.nDoor)
		{
			if (newPlayer.coord.Y == 1 && newPlayer.coord.X == (room.xSize / 2))
			{
				newPlayer.coord.Y = abs(1 - (room.ySize - 1));
				newPlayer.pos = (room.nDoor == -1 ? 0 : room.nDoor);
				drawRoom();
				drawInfo();
				enemy = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos].enemy;
				drawEntities(coord, newPlayer.coord, newPlayer.marker);
				drawEntities(coord, enemy.coord, enemy.marker);
				return 1;
			}
		}
		break;
	case 2:
		if (room.sDoor)
		{
			if (newPlayer.coord.Y == room.ySize - 2 && newPlayer.coord.X == (room.xSize / 2))
			{
				newPlayer.coord.Y = abs(newPlayer.coord.Y - (room.ySize - 1));
				newPlayer.pos = (room.sDoor == -1 ? 0 : room.sDoor);
				drawRoom();
				drawInfo();
				enemy = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos].enemy;
				drawEntities(coord, newPlayer.coord, newPlayer.marker);
				drawEntities(coord, enemy.coord, enemy.marker);
				return 1;
			}
		}
		break;
	case 3:
		if (room.wDoor)
		{
			if (newPlayer.coord.X == 1 && newPlayer.coord.Y == (room.ySize / 2))
			{
				newPlayer.coord.X = abs(1 - (room.xSize - 1)); 
				newPlayer.pos = (room.wDoor == -1 ? 0 : room.wDoor);
				drawRoom();
				drawInfo();
				enemy = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos].enemy;
				drawEntities(coord, newPlayer.coord, newPlayer.marker);
				drawEntities(coord, enemy.coord, enemy.marker);
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
				newPlayer.pos = (room.eDoor == -1 ? 0 : room.eDoor);
				drawRoom();
				drawInfo();
				enemy = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos].enemy;
				drawEntities(coord, newPlayer.coord, newPlayer.marker);
				drawEntities(coord, enemy.coord, enemy.marker);
				return 1;
			}
		}
		break;
	}

	return 0;
}

void drawRoom()
{//Door coded for 2 slots at halfway point of wall
	struct Room room = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];

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

void drawInfo()
{
	printf("\n\n\n");
	printf("HP: ");
	for (int i = 0; i < newPlayer.maxHealth; i++)
	{
		printf("%c", (newPlayer.health > i ? 47 : 46));
	}
	printf("  %d/%d", newPlayer.health, newPlayer.maxHealth);
}

