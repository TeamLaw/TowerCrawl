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

#define _CRT_SECURE_NO_WARNINGS 1

#include <Windows.h>
#include <math.h>
#include <time.h>

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
	int exp;
};

struct Player
{
	struct Sprite;
	struct Room * roomLoc;
	int level;
	int experience;
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
	int isPortal;
	int entered;
	struct Room * nDoor;
	struct Room * sDoor;
	struct Room * eDoor;
	struct Room * wDoor;	
	struct Entity portal;
	struct Enemy enemy;
};

//enum to pass player choice , I thought it was less confusing than using ints
enum PlayerChoice
{
	Attack,
	Use_Potion,
	Wait,
	Cheat,
};
struct Room * delPointers[1000];
int delCounter;

struct Room * floorEnd;

struct Player player;
time_t t;
int difficulty;
int branch;
int location;

//Game.c
void createPlayer();
struct Room * createRoom();
int openDoors(struct Room *);
int createEnemies(struct Room *, int);
int checkPlayerPos(int, struct Room *);
void drawRoom(struct Room *);
void drawInfo();
void playerMove();
void enemyMove();
void drawEntities(COORD, COORD, char);
void moveCursor(int, int);
int randomNum(int, int);//accepts min and max integer and returns: min <= num < max
int checkInteraction();
int coordCompare(COORD, COORD);
int minCheck(int);
void drawEncounters(struct Enemy *);
void gameLogic(struct Enemy *, enum PlayerChoice);
void MonsterAction(struct Enemy *);
int handleEncounter(struct Enemy *);
void ShowPlayerStats();
void displayDeathScreen();
void clearMemory();
void createFloor();

#endif