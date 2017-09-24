#include "CreateWorld.h"

void createPlayer(struct Player * player)
{//hardcoded player info
	player->marker = 'o';
	player->pos = 0;
	player->floorLoc = 0;
	player->coord.X = 5;
	player->coord.Y = 5;
	player->maxHealth = 10;
	player->health = 10;
	player->damage = 3;
	player->roomCheck = 0;
}

void createTower(struct Tower * tower, int dif)
{
	int newDoor = 0, oldDoor = 0, pos = 0;

	struct Floor * floor;
	struct Room * room;

	for (int i = 0; i < sizeof(tower->floors) / sizeof(tower->floors[0]); i++)
	{
		floor = &tower->floors[i];

		for (int j = 0; j < (10 + (dif * 5)); j++)
		{
			room = &floor->rooms[j];

			room->xSize = (11 + (5 * dif));
			room->ySize = (11 + (5 * dif));

			do { newDoor = randomNum(1, 5); } while (oldDoor == newDoor);
			
			if (j == (10 + (dif * 5)) - 1) { newDoor = 0; }
			room->nDoor = (oldDoor == 1 ? (pos == 1 ? -1 : pos - 1) : (newDoor == 1 ? pos + 1 : 0));
			room->sDoor = (oldDoor == 2 ? (pos == 1 ? -1 : pos - 1) : (newDoor == 2 ? pos + 1: 0));
			room->wDoor = (oldDoor == 3 ? (pos == 1 ? -1 : pos - 1) : (newDoor == 3 ? pos + 1: 0));
			room->eDoor = (oldDoor == 4 ? (pos == 1 ? -1 : pos - 1) : (newDoor == 4 ? pos + 1: 0));

			oldDoor = newDoor + (newDoor % 2 ? 1 : -1);
			pos++;
			int check = (j == (10 + (dif * 5)) - 1);
			if (pos > 1) 
			{ 
				if (createEnemies(room, dif, (j == (10 + (dif * 5)) - 1)))
				{
					room->portal.coord.X = (room->xSize / 2);
					room->portal.coord.Y = (room->ySize / 2);
					room->portal.marker = '@';
				}
			}//Last room holds a boss
		}
	}
}

int createEnemies(struct Room * room, int dif, int isBoss)
{//only making 1 enemy atm, have to work out some sort of collision or sometin for multiple, might just stick with 1 enemy per room and just increase stats
	room->enemy.coord.X = (room->xSize / 2); 
	room->enemy.coord.Y = (room->ySize / 2);
	room->enemy.maxHealth = ((3 + (dif * 2)) * (isBoss ? 2 : 1));
	room->enemy.health = ((3 + (dif * 2)) * (isBoss ? 2 : 1));
	room->enemy.damage = ((1 + (dif * 1)) * (isBoss ? 2 : 1));
	room->enemy.marker = (isBoss ? '#' : 'x');
	room->enemy.isBoss = isBoss;
	//room->enemy.loot = 

	return isBoss;
}