#include <Windows.h>

#ifndef TOWERCRAWL_H_
#define TOWERCRAWL_H_

struct Entity
{
	char marker;
	COORD coord;
};

struct Sprite
{
	struct Entity;
	int health;
	int maxHealth;
	int damage;
};

struct Player
{
	struct Sprite;
	int floorLoc;
	int pos;
	int level;
	int roomCheck;
};

struct Enemy
{
	struct Sprite;
	int isBoss;//0 = normal enemy, 1 = boss
	int loot;//0 = no loot, 1 = armor(max hp), 2 = weapon(damage), 3 = potion(healing)
};

struct Room
{//One enemy per room
	int xSize;
	int ySize;
	int nDoor;
	int sDoor;
	int eDoor;
	int wDoor;
	int isPortal;
	struct Entity portal;
	struct Enemy enemy;
};

struct Floor
{//Hardcoded 3x3 rooms for the floor
	struct Room rooms[25];
};

struct Tower
{//Hardcoded 7 floors
	struct Floor floors[3];
};

void createPlayer(struct Player *);
void createTower(struct Tower *, int);
void createEntities(struct Room *, int);
int checkPlayerPos(int);
void drawRoom();
void drawInfo();
void playerMove();
void enemyMove();
void drawEntities(COORD, COORD, char);
void moveCursor(int, int);
int randomNum(int, int);//accepts min and max integer and returns: min <= num < max
void checkInteraction();

#endif

