#include "TowerCrawl.h"

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
	}

	room = player.roomLoc;
	if (room->isPortal) { drawEntities(coord, room->portal.coord, room->portal.marker); }
	if (roomChange) 
	{ 
		coord.X = 0, coord.Y = 0; 
		if (!room->entered) 
		{ 
			openDoors(player.roomLoc);
			if (createEnemies(player.roomLoc, minCheck()))
			{
				floorEnd = room;
				room->portal.coord.X = (room->xSize / 2);
				room->portal.coord.Y = (room->ySize / 2);
				room->portal.marker = '@';
			}
		}

		drawRoom(player.roomLoc);
		drawInfo();
		if (room->enemy.health) { drawEntities(coord, room->enemy.coord, room->enemy.marker); }
	}

	drawEntities(coord, player.coord, player.marker);
}

int checkPlayerPos(int direction, struct Room * oldRoom)
{
	struct Room * newRoom;
	COORD coord = { 0, 0 };

	switch (direction)
	{
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
// -1 death
int checkInteraction()
{
	int interactionResult = 0;

	struct Room * room = player.roomLoc;
	struct Enemy * enemy = &room->enemy;
	COORD coord = { 0, 0 };

	if (coordCompare(player.coord, enemy->coord) && enemy->health)
	{
		interactionResult = handleEncounter(&player, enemy);
		if (!interactionResult)
		{
			player.coord.X += (player.coord.X <= room->xSize / 2 ? (room->xSize / 3) : -(room->xSize / 3));
			player.coord.Y += (player.coord.Y <= room->ySize / 2 ? (room->ySize / 3) : -(room->ySize / 3));
			drawRoom(room);
			drawInfo();
			drawEntities(coord, player.coord, player.marker);
			if (enemy->health) { drawEntities(coord, enemy->coord, enemy->marker); }
			if (room->isPortal) { drawEntities(coord, room->portal.coord, room->portal.marker); }
		}
		else if (interactionResult == 1)
		{
			drawRoom(room);
			drawInfo();

			if (enemy->isBoss)
			{
				player.coord.Y += (player.coord.X == room->xSize / 2 && player.coord.Y == room->ySize / 2 ? 2 : 0);
				room->isPortal = 1;
				drawEntities(coord, room->portal.coord, room->portal.marker);
			}
			drawEntities(coord, player.coord, player.marker);
		}
		else if (interactionResult == -1)
		{
			displayDeathScreen();
			return;
		}
	}
}