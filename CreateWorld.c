#include "TowerCrawl.h"

void createPlayer()
{//hardcoded player info
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
}

void createFloor()
{
	branch = 50;

	player.roomLoc = createRoom(1);
	player.coord.X = player.roomLoc->xSize / 2;
	player.coord.Y = player.roomLoc->ySize / 2;
	openDoors(player.roomLoc);

	drawRoom(player.roomLoc);
	drawInfo();
	drawLegend();
	drawEntities((COORD) { 0, 0 }, player.coord, player.marker);
}

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

int createEnemies(struct Room * room, int bossCheck)
{//only making 1 enemy atm, have to work out some sort of collision or sometin for multiple, might just stick with 1 enemy per room and just increase stats
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

void createNPCs()
{

}