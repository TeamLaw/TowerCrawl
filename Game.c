
#include "TowerCrawl.h"

//Save game to file?

struct Player newPlayer;
struct Tower tower;
time_t t;
int difficulty = 0;

int main()
{
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

int coordCompare(COORD coord1, COORD coord2)//OVERLOAD OPERATORS IN C++!!!
{
	return (coord1.X == coord2.X && coord1.Y == coord2.Y);
}

void checkInteraction()
{
	int interactionResult = 0;

	struct Room * room = &tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];
	struct Enemy * enemy = &room->enemy;
	COORD coord = { 0, 0 };
	
	if (coordCompare(newPlayer.coord, enemy->coord) && enemy->health)
	{
		interactionResult = handleEncounter(&newPlayer, enemy);
		if (!interactionResult)
		{
			newPlayer.coord.X += (newPlayer.coord.X <= room->xSize / 2 ? (room->xSize / 3) : -(room->xSize / 3));
			newPlayer.coord.Y += (newPlayer.coord.Y <= room->ySize / 2 ? (room->ySize / 3) : -(room->ySize / 3));
			drawRoom();
			drawInfo();
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
			if (enemy->health) { drawEntities(coord, enemy->coord, enemy->marker); }
			if (room->isPortal) { drawEntities(coord, room->portal.coord, room->portal.marker); }
		}
		else if (interactionResult == 1)
		{		
			drawRoom();
			drawInfo();
			
			if (enemy->isBoss && newPlayer.floorLoc < 2)
			{
				newPlayer.coord.Y += (newPlayer.coord.X == room->xSize / 2 && newPlayer.coord.Y == room->ySize / 2 ? 2 : 0);
				room->isPortal = 1;
				tower.floors[newPlayer.floorLoc + 1].rooms[0].isPortal = 1;
				drawEntities(coord, room->portal.coord, room->portal.marker);
			}
			drawEntities(coord, newPlayer.coord, newPlayer.marker);
		}
		else if (interactionResult == -1)
		{
			// adding stuff here, clear the screen. print some death animation
			//
			displayDeathScreen();

			_getch();
			return;
		}
	}
	else if (coordCompare(newPlayer.coord, room->portal.coord) && room->isPortal)
	{
		newPlayer.coord.Y += (newPlayer.coord.X == room->xSize / 2 && newPlayer.coord.Y == room->ySize / 2 ? 2 : 0);
		if (newPlayer.pos)
		{
			newPlayer.floorLoc++;
			newPlayer.pos = 0;
		}
		else
		{
			newPlayer.floorLoc--;
			newPlayer.pos = (sizeof(tower.floors[newPlayer.floorLoc].rooms) / sizeof(tower.floors[newPlayer.floorLoc].rooms[0]) - (11 - (difficulty * 5)));
		}
		drawRoom();
		drawInfo();
		drawEntities(coord, newPlayer.coord, newPlayer.marker);
		drawEntities(coord, room->portal.coord, room->portal.marker);
	}
}
	
void drawEntities(COORD oldCoord, COORD coord, char marker)
{
	if (oldCoord.X || oldCoord.Y)
	{
		moveCursor(oldCoord.X, oldCoord.Y);
		printf(" ");
	}

	moveCursor(coord.X, coord.Y);
	printf("%c", marker);

	moveCursor(0, 0);
}

/*moveCursor(int x, int y) moves the cursor to x and y location on command prompt
Parameters: 
	X- x Location
	Y- Y Location
Returns: 
	nothing(Void)
*/
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

/*enemyMove() selects the monster that is in the same room as the player,
	Then it has the monster move toward the player
Parameters: 
	none
Returns: 
	nothing(Void)
*/
void enemyMove()
{
	struct Enemy * enemy = &tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos].enemy;
	COORD coord = { enemy->coord.X, enemy->coord.Y };

	if (abs(enemy->coord.X - newPlayer.coord.X) > abs(enemy->coord.Y - newPlayer.coord.Y))
	{
		enemy->coord.X += (enemy->coord.X < newPlayer.coord.X ? 1 : -1);
	}
	else { enemy->coord.Y += (enemy->coord.Y < newPlayer.coord.Y ? 1 : -1); }
	
	if (enemy->health) { drawEntities(coord, enemy->coord, enemy->marker); }
}

/*playerMove() handles input during the player move phase 
Parameters: 
	none
Returns: 
	nothing(Void)
*/
void playerMove()
{
	COORD coord = newPlayer.coord;
	struct Room room = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];

	switch (getch())
	{
		//Player moves up on game screen
	case 'w':
		if (checkPlayerPos(1, room));
		else if (newPlayer.coord.Y > 1) { newPlayer.coord.Y--; }
		break;
		//Player moves down on game screen
	case 's':
		if (checkPlayerPos(2, room));
		else if (newPlayer.coord.Y < (room.ySize - 2)) { newPlayer.coord.Y++; }
		break;
		//Player moves left on game screen
	case 'a':
		if (checkPlayerPos(3, room));
		else if (newPlayer.coord.X > 1) { newPlayer.coord.X--; }
		break;
		//Player moves right on game screen
	case 'd':
		if (checkPlayerPos(4, room));
		else if (newPlayer.coord.X < (room.xSize - 2)) { newPlayer.coord.X++; }
		break;
	case 'c':
		ShowPlayerStats(&newPlayer);
		//Have to redraw the entire room
		drawRoom();


		break;
	}
	room = tower.floors[newPlayer.floorLoc].rooms[newPlayer.pos];
	if (room.isPortal) { drawEntities(coord, room.portal.coord, room.portal.marker); }
	drawEntities(coord, newPlayer.coord, newPlayer.marker);
}

int checkPlayerPos(int direction, struct Room room)
{
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
				if (enemy.health) { drawEntities(coord, enemy.coord, enemy.marker); }
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
				if (enemy.health) { drawEntities(coord, enemy.coord, enemy.marker); }
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
				if (enemy.health) { drawEntities(coord, enemy.coord, enemy.marker); }
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
				if (enemy.health) { drawEntities(coord, enemy.coord, enemy.marker); }
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
	printf("\nFloor: %d Room: %d\n\n", newPlayer.floorLoc + 1, newPlayer.pos + 1);
	printf("HP: ");
	for (int i = 0; i < newPlayer.maxHealth; i++)
	{
		printf("%c", (newPlayer.health > i ? 47 : 46));
	}
	printf("  %d/%d", newPlayer.health, newPlayer.maxHealth);
}

