#include <stdio.h>
#include <math.h>
#include <conio.h>


int xPlayer = 5, yPlayer = 5;//Player movement limited 0-13, Room is 16x16 minus walls and ceilings leave 14x14 (13x13 since you start at index 0)
int playerLocation = 0;//Tracks which room the player is in...dynamic room creation...have to save player previous rooms though...

int checkPlayerPos(int, int, int, struct roomTemplate);
void drawRoom(struct roomTemplate);
void drawHealth();
void playerMove(struct roomTemplate);
void createEnemies();

struct sprite {
	int xSprite;
	int ySprite;
	int row;
	int col;
	int health;
	int maxHealth;
};

struct roomTemplate {
    int nDoor;
	int sDoor;
	int eDoor;
	int wDoor;
};

struct sprite newPlayer;


int main()
{
	newPlayer.row = 0;
	newPlayer.col = 0;
	newPlayer.xSprite = 5;
	newPlayer.ySprite = 5;
	newPlayer.maxHealth = 10;
	newPlayer.health = 10;

	//struct roomTemplate tower[7];
	struct roomTemplate rooms[3][3];
	struct sprite enemies[9];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rooms[i][j].nDoor = (i != 0 ? 1 : 0);
			rooms[i][j].sDoor = (i != 2 ? 1 : 0);
			rooms[i][j].eDoor = (j != 2 ? 1 : 0);
			rooms[i][j].wDoor = (j != 0 ? 1 : 0);
		}
	}

	while (1)
	{
		system("cls");
		drawRoom(rooms[newPlayer.row][newPlayer.col]);
		drawHealth();
		playerMove(rooms[newPlayer.row][newPlayer.col]);
	}
	
	return 0;
}

void createEnemies()
{

}

void playerMove(struct roomTemplate room)
{
	switch (getch())
	{
	case 'w':
		if (checkPlayerPos(room.nDoor, 0, 0, room));
		else if (yPlayer > 0) { yPlayer--; }
		break;
	case 'a':
		if (checkPlayerPos(room.wDoor, 1, 0, room));
		else if (xPlayer > 0) { xPlayer--; }
		break;
	case 's':
		if (checkPlayerPos(room.sDoor, 0, 13, room));
		else if (yPlayer < 13) { yPlayer++; }
		break;
	case 'd':
		if (checkPlayerPos(room.eDoor, 1, 13, room));
		else if (xPlayer < 13) { xPlayer++; }
		break;
	}
}

int checkPlayerPos(int doorCheck, int locCheck, int newPos, struct roomTemplate room)
{
	if (doorCheck)
	{
		if (locCheck)
		{
			if (xPlayer == newPos && (yPlayer == 6 || yPlayer == 7))
			{
				xPlayer = abs(newPos - 13);
				newPlayer.col += (newPos ? 1 : -1);
				return 1;
			}
		}
		else
		{
			if (yPlayer == newPos && (xPlayer == 6 || xPlayer == 7))
			{
				yPlayer = abs(newPos - 13);
				newPlayer.row += (newPos ? 1 : -1);
				return 1;
			}
		}
	}
	return 0;
}

void drawRoom(struct roomTemplate room)
{
	int xRoom = 16, yRoom = 16;

	for (int n = 0; n < xRoom; n++) 
	{ 
		if ((n == 7 || n == 8) && room.nDoor) { printf(" "); }
		else { printf("="); }
	}
	printf("\n");
	for (int y = 0; y < yRoom - 2; y++)
	{
		if ((y == 6 || y == 7) && room.wDoor) { printf(" "); }
		else { printf("["); }
		for (int x = 0; x < xRoom - 2; x++) 
		{ 
			if (y == yPlayer && x == xPlayer) { printf("o"); }
			else { printf(" "); }
		}
		if ((y == 6 || y == 7) && room.eDoor) { printf(" \n"); }
		else { printf("]\n"); }
	}
	for (int s = 0; s < xRoom; s++) 
	{ 
		if ((s == 7 || s == 8) && room.sDoor) { printf(" "); }
		else { printf("="); }
	}
}

void drawHealth()
{
	printf("\n\n\n");

	printf("HP: ");
	for (int i = 0; i < 10; i++)
	{
		printf("%c", (newPlayer.health > i ? 47 : 46));
	}
	printf("  %d/%d", newPlayer.health, newPlayer.maxHealth);
}