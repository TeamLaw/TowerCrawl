
#define _CRT_SECURE_NO_WARNINGS 1
/*CreateWorld.c
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
*/

#include "TowerCrawl.h"
#include <string.h>


/*createPlayer()
hardcoded player info
Parameters:
None
Returns:
	Void
Programmer: Law
*/
void createPlayer()
{
	int dif;

	player.marker = 'O';
	player.coord.X = 0;
	player.coord.Y = 0;
	player.maxHealth = 100;
	player.health = player.maxHealth;
	player.damage = 5;
	player.money = 10;
	player.exp = 0;
	player.level = 1;
	player.roomLoc = NULL;
	player.name[21] = 0;
	player.inventory[0] = (struct Item) { "Club", 25, 0, 0, 2 };
	
	printf("What shall we call you, your lordship? (enter player name - max 20 characters long): \n");
	fgets(player.name, 20, stdin);
	int length = strlen(player.name);
	for (int i = 0; i < length; i++)
	{
		if ((int)player.name[i] == 10) { player.name[i] = 0; }
	}
	printf("%s, how bad shall we make your day? (1)Normal (2)So Intense (3)Insanely Bad Day", player.name);
	dif = _getch() - 49;
	difficulty = (dif >= 0 && dif <= 2 ? dif : 100); // removing form the ASCII character value
}


/*createFloor()
Creates floor
Parameters:
None
Returns:
Void
Programmer: Law
*/
void createFloor()
{
	branch = 50;

	player.roomLoc = createRoom(1);
	player.coord.X = player.roomLoc->xSize / 2;
	player.coord.Y = player.roomLoc->ySize / 2;
	openDoors(player.roomLoc);

	floorStart = player.roomLoc;

	reDraw('r');
	reDraw('c');
	reDraw('n');
}

/*createRoom()
Creates Rooms using generation code
Parameters:
room 
Returns:
returns pointer to room
Programmer: Law
*/
struct Room * createRoom(int base)

{
	struct Room * room = malloc(sizeof(struct Room));
	room->xSize = (base ? 17 : randomNum(9, 22));
	room->ySize = (base ? 17 : randomNum(9, 22));
	room->entered = 0;

	room->nDoor = NULL;
	room->sDoor = NULL;
	room->wDoor = NULL;
	room->eDoor = NULL;

	room->enemy.health = 0;
	
	room->isPortal = 0;
	room->portal.coord.X = (room->xSize / 2);
	room->portal.coord.Y = (room->ySize / 2);
	room->portal.marker = '@';

	delPointers[delCounter] = room;
	delCounter++;
			
	return room;
}

/*openDoors(struct Room * room)
Generates the next room the player is walking into including the doors
Parameters:
 Room - the room that is being created
Returns:
returns number of doors
Programmer: Law
*/
int openDoors(struct Room * room)
{
	int counter = 0;

RETRY:
	if (!room->nDoor)
	{
		room->nDoor = (randomNum(1, 100) < branch ? createRoom(0) : room->nDoor);
		counter += (room->nDoor ? 1 : 0);
	}
	if (!room->sDoor)
	{
		room->sDoor = (randomNum(1, 100) < branch ? createRoom(0) : room->sDoor);
		counter += (room->sDoor ? 1 : 0);
	}
	if (!room->wDoor)
	{
		room->wDoor = (randomNum(1, 100) < branch ? createRoom(0) : room->wDoor);
		counter += (room->wDoor ? 1 : 0);
	}
	if (!room->eDoor)
	{
		room->eDoor = (randomNum(1, 100) < branch ? createRoom(0) : room->eDoor);
		counter += (room->eDoor ? 1 : 0);
	}
	if (minCheck(1) && delCounter < 10) { goto RETRY; }

	branch -= (counter ? (counter - 1) * 5 : 0);
	room->entered = 1;

	return counter;
}

/*createEnemies(struct Room * room, int bossCheck)
only making 1 enemy atm, have to work out some sort of collision or sometin for multiple, might just stick with 1 enemy per room and just increase stats
Parameters:
 room - the room that is being accessed
 bosscheck - the modifier number that decides if there is a boss in this room
Returns:
 1 - if this is a boss
Programmer: Law
*/
int createEnemies(struct Room * room, int bossCheck)
{
	int isBoss = (((delCounter > 10 && randomNum(1, 101) < delCounter) || bossCheck) && !floorEnd), \
		multiplier = location + difficulty + isBoss;
	room->enemy.coord.X = randomNum(1, room->xSize - 1); 
	room->enemy.coord.Y = randomNum(1, room->ySize - 1);
	room->enemy.maxHealth = randomNum(5, 11) * multiplier;
	room->enemy.health = room->enemy.maxHealth;
	room->enemy.damage = randomNum(2, 6) * multiplier;
	room->enemy.exp = 25 * (multiplier);
	room->enemy.marker = (isBoss ? '#' : 'x');
	room->enemy.isBoss = isBoss;
	room->enemy.money = randomNum(2, 11) * multiplier;

	return isBoss;
}

/*createNPCs()
Populates the 3 NPC structs with information and displays them on screen
Parameters:
none
Returns:
none
Programmer: Law
*/
void createNPCs()
{
	struct Room * room = player.roomLoc;

	shopkeeper.coord.X = 2;
	shopkeeper.coord.Y = 2;
	shopkeeper.marker = 'S';
	strcpy(shopkeeper.name, "Shopkeeper");
	shopkeeper.merchandise[0] = (struct Item) { "Small Health Potion", 10, 10, 0, 0 };
	shopkeeper.merchandise[1] = (struct Item) { "Health Potion", 50, 25, 0, 0 };
	shopkeeper.merchandise[2] = (struct Item) { "Large Health Potion", 100, 50, 0, 0 };

	blacksmith.coord.X = 2;
	blacksmith.coord.Y = room->ySize - 3;
	blacksmith.marker = 'B';
	strcpy(shopkeeper.name, "Blacksmith");
	blacksmith.merchandise[0] = (struct Item) { "Club", 25, 0, 0, 2 };
	blacksmith.merchandise[1] = (struct Item) { "sword", 100, 0, 0, 5 };
	blacksmith.merchandise[2] = (struct Item) { "Great Axe", 250, 0, 0, 10 };
	blacksmith.merchandise[3] = (struct Item) { "Cloth Armor", 10, 0, 5, 0 };
	blacksmith.merchandise[4] = (struct Item) { "Leather Armor", 100, 0, 15, 0 };
	blacksmith.merchandise[5] = (struct Item) { "Studded Armor", 250, 0, 50, 0 };
	blacksmith.merchandise[6] = (struct Item) { "Plate Armor", 500, 0, 100, 0 };

	innkeeper.coord.X = room->xSize - 3;
	innkeeper.coord.Y = 2;
	innkeeper.marker = 'I';
	strcpy(innkeeper.name, "Innkeeper");

	drawEntities((COORD) { 0, 0 }, shopkeeper.coord, shopkeeper.marker);
	drawEntities((COORD) { 0, 0 }, blacksmith.coord, blacksmith.marker);
	drawEntities((COORD) { 0, 0 }, innkeeper.coord, innkeeper.marker);
}