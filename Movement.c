
/*Movement.c 
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
*/


#include "TowerCrawl.h"
/*
enemyMove() determines where the monster in the player's current room
Parameters :
	None
Returns :
	void
Programmer: Law
*/
void enemyMove()
{
	struct Enemy * enemy = &player.roomLoc->enemy;
	COORD coord = { enemy->coord.X, enemy->coord.Y };

	if (abs(enemy->coord.X - player.coord.X) > abs(enemy->coord.Y - player.coord.Y))
	{
		enemy->coord.X += (enemy->coord.X < player.coord.X ? 1 : -1);
	}
	else { enemy->coord.Y += (enemy->coord.Y < player.coord.Y ? 1 : -1); }

	if (enemy->health) { drawEntities(coord, enemy->coord, enemy->marker); }
}

/*
playerMove() handles the player's input 
Parameters :
	None
Returns :
	void
Programmer: Law
*/
void playerMove()
{
	int roomChange = 0;
	COORD coord = player.coord;
	struct Room * room = player.roomLoc;

	switch (getch())
	{
	case 'w':
		roomChange = (checkPlayerPos(1, room));
		player.coord.Y -= (!roomChange &&player.coord.Y > 1);
		break;
	case 's':
		roomChange = (checkPlayerPos(2, room));
		player.coord.Y += (!roomChange && player.coord.Y < (room->ySize - 2));
		break;
	case 'a':
		roomChange = (checkPlayerPos(3, room));
		player.coord.X -= (!roomChange && player.coord.X > 1);
		break;
	case 'd':
		roomChange = (checkPlayerPos(4, room));
		player.coord.X += (!roomChange && player.coord.X < (room->xSize - 2));
		break;
	case 'c':
		ShowPlayerStats();
		break;
	}

	room = player.roomLoc;
	if (room->isPortal) { drawEntities((COORD) { 0, 0 }, room->portal.coord, room->portal.marker); }
	if (roomChange) 
	{ 
		if (!room->entered)	
		{ 
			openDoors(player.roomLoc);
			if (createEnemies(player.roomLoc, minCheck(0)))
			{
				floorEnd = room;
				room->portal.coord.X = (room->xSize / 2);
				room->portal.coord.Y = (room->ySize / 2);
				room->portal.marker = '@';
			}
		}

		drawRoom(player.roomLoc);
		drawInfo();
		drawLegend();
		if (room->enemy.health > 0) { drawEntities((COORD) { 0, 0 }, room->enemy.coord, room->enemy.marker); }

	}

	drawEntities((roomChange ? (COORD) { 0, 0 } : coord), player.coord, player.marker);
}

/*
checkPlayerPos(int direction, struct Room * oldRoom) checks for to see if the player has ran into portals or monsters
Parameters :
	direction - Which direction the player is moving 
		1 -North 2- South 3- West 4- East
	oldRoom - a pointer that hold the value of the room a player is leaving if he changes rooms.
Returns :
1 - moves through door

Programmer: Law
*/
int checkPlayerPos(int direction, struct Room * oldRoom)
{
	struct Room * newRoom;

	switch (direction)
	{
		//player is moving North
	case 1:
		if (oldRoom->nDoor)
		{
			if (player.coord.Y == 1 && player.coord.X == (oldRoom->xSize / 2))
			{
				newRoom = oldRoom->nDoor;
				newRoom->sDoor = (!newRoom->sDoor ? player.roomLoc : newRoom->sDoor);
				
				player.roomLoc = newRoom;
				player.coord.X = newRoom->xSize / 2;
				player.coord.Y = newRoom->ySize - 2;

				return 1;
			}
		}
		break;
		//player is moving South
	case 2:
		if (oldRoom->sDoor)
		{
			if (player.coord.Y == oldRoom->ySize - 2 && player.coord.X == (oldRoom->xSize / 2))
			{
				newRoom = oldRoom->sDoor;
				newRoom->nDoor = (!newRoom->nDoor ? player.roomLoc : newRoom->nDoor);
				
				player.roomLoc = newRoom;
				player.coord.X = newRoom->xSize / 2;
				player.coord.Y = 1;

				return 1;
			}
		}
		break;
		//player is moving West
	case 3:
		if (oldRoom->wDoor)
		{
			if (player.coord.X == 1 && player.coord.Y == (oldRoom->ySize / 2))
			{
				newRoom = oldRoom->wDoor;
				newRoom->eDoor = (!newRoom->eDoor ? player.roomLoc : newRoom->eDoor);
				
				player.roomLoc = newRoom;
				player.coord.X = newRoom->xSize - 2;
				player.coord.Y = newRoom->ySize / 2;
				
				return 1;
			}
		}
		break;
		//player is moving East
	case 4:
		if (oldRoom->eDoor)
		{
			if (player.coord.X == oldRoom->xSize - 2 && player.coord.Y == (oldRoom->ySize / 2))
			{
				newRoom = oldRoom->eDoor;
				newRoom->wDoor = (!newRoom->wDoor ? player.roomLoc : newRoom->wDoor);
				
				player.roomLoc = newRoom;
				player.coord.X = 1;
				player.coord.Y = newRoom->ySize / 2;
				
				return 1;
			}
		}
		break;
	}

	return 0;
}

/*
checkInteraction() checks for to see if the player has ran into portals or monsters
Parameters :
	None
Returns :
	-1 - if player dies

Programmer: Law, Neumann
*/
int checkInteraction()
{
	int interactionResult = 0;
	struct Room * room = player.roomLoc;
	struct Enemy * enemy = &room->enemy;

	if (coordCompare(player.coord, enemy->coord) && enemy->health > 0)
	{
		//Text combat
		interactionResult = handleEncounter(enemy);
		if (!interactionResult)
		{
			player.coord.X += (player.coord.X <= room->xSize / 2 ? (room->xSize / 3) : -(room->xSize / 3));
			player.coord.Y += (player.coord.Y <= room->ySize / 2 ? (room->ySize / 3) : -(room->ySize / 3));
			drawRoom(room);
			drawInfo();
			drawLegend();
			drawEntities((COORD) { 0, 0 }, player.coord, player.marker);
			if (enemy->health) { drawEntities((COORD) { 0, 0 }, enemy->coord, enemy->marker); }
			if (room->isPortal) { drawEntities((COORD) { 0, 0 }, room->portal.coord, room->portal.marker); }
		}
		else if (interactionResult == 1)
		{
			drawRoom(room);
			drawInfo();
			drawLegend();

			if (enemy->isBoss)
			{
				player.coord.Y += (player.coord.X == room->xSize / 2 && player.coord.Y == room->ySize / 2 ? 2 : 0);
				room->isPortal = 1;
				drawEntities((COORD) { 0, 0 }, room->portal.coord, room->portal.marker);
			}
			drawEntities((COORD) { 0, 0 }, player.coord, player.marker);
		}
		else if (interactionResult == -1)
		{
			displayDeathScreen();
			return -1;
		}
	}

	//checking to see if the character has walked into a portal

	if (coordCompare(player.coord, room->portal.coord) && room->isPortal)
	{
		clearMemory();
		if (location != (difficulty + 3))
		{
			location++;
			floorEnd = NULL;
			createFloor();
		}
		else
		{
			//Game over, you win!

		}
	}
}