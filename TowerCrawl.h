/*TowerCrawl.h
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
*/
#ifndef stdio 
#define stdio 1
#include <stdio.h>
#endif

#ifndef conio
#define conio 1
#include <conio.h>
#endif

//TowerCrawl will only run once
#ifndef TOWERCRAWL_H_
#define TOWERCRAWL_H_ 1
#define invSizeLimit 10
#define merchSizeLimit 10

#include <Windows.h>
#include <math.h>
#include <time.h>

class Coordinate {
public:
	int x, y;
	bool operator==(const Coordinate c1)const { return this->x == c1.x && this->y == c1.y; }
};

class Item {
public:
	char name[100];
	int value;
	int health;
	int maxHealth;
	int damage;
};

class Entity {
public:
	char marker;
	char name[21];
	Coordinate coord;
};

class Sprite : public Entity {
public:
	int health;
	int maxHealth;
	int damage;
	int exp;
	int level;
	int money;
};

class Player : public Sprite {
public:
	class Room * roomLoc;
	int experience;
	Item inventory[invSizeLimit];
	Item * weapon;
	Item * armor;
};

class NPC : public Entity {
public:
	Item merchandise[merchSizeLimit];
};

class Enemy : public Sprite {
public:
	Item loot;
	int isBoss;//0 = normal enemy, 1 = boss
};

class Room {
public:
	int xSize;
	int ySize;
	int isPortal;
	int entered;
	Room * nDoor;
	Room * sDoor;
	Room * eDoor;
	Room * wDoor;
	Entity portal;
	Enemy enemy;
};

//enum to pass player choice , I thought it was less confusing than using ints
enum PlayerChoice
{
	Attack,
	Use_Item,
	Wait,
	Cheat,
};

extern Room * delPointers[1000];
extern int delCounter;

extern Room * floorStart;
extern Room * floorEnd;

extern Player player;
extern NPC shopkeeper;
extern NPC innkeeper;
extern NPC blacksmith;

extern time_t t;
extern int difficulty;
extern int branch;
extern int location;

//Game.c
void createPlayer();
class Room * createRoom(int);
int openDoors(Room *);
int createEnemies(Room *, int);
int checkPlayerPos(int, Room *);
void drawRoom(Room *);
void drawInfo();
void drawLegend();
void playerMove();
void enemyMove();
void drawEntities(Coordinate, Coordinate, char);
void moveCursor(int, int);
int randomNum(int, int);//accepts min and max integer and returns: min <= num < max
int checkInteraction();
int coordCompare(Coordinate, Coordinate);
int minCheck(int);
void drawEncounters(Enemy *);
void gameLogic(Enemy *, enum PlayerChoice);
void MonsterAction(Enemy *);
int handleEncounter(Enemy *);
void ShowPlayerStats();
void displayDeathScreen();
void clearMemory();
void createFloor();
void createNPCs();
void printGameIntroMessage();
int displayInventory(Item *, int, int);
void npcInteraction(NPC *, int);
void reDraw(char);
int inventoryInteraction(Item *, int, char, int);
int inventoryCheck(int);
int inventoryProcess(Item *, char, int, int);

#endif