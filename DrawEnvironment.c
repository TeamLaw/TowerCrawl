#include "TowerCrawl.h"

void drawRoom(struct Room * room)
{//Door coded for 2 slots at halfway point of wall
	system("cls");
	for (int n = 0; n < room->xSize; n++)
	{
		if ((n == (room->xSize / 2)) && room->nDoor) { printf(" "); }
		else { printf("="); }
	}
	printf("\n");
	for (int y = 0; y < room->ySize - 2; y++)
	{
		if ((y == (room->ySize / 2 - 1)) && room->wDoor) { printf(" "); }
		else { printf("["); }
		for (int x = 0; x < room->xSize - 2; x++) { printf(" "); }
		if ((y == (room->ySize / 2 - 1)) && room->eDoor) { printf(" \n"); }
		else { printf("]\n"); }
	}
	for (int s = 0; s < room->xSize; s++)
	{
		if ((s == (room->xSize / 2)) && room->sDoor) { printf(" "); }
		else { printf("="); }
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

void drawInfo()
{
	printf("\nFloor: %d Branch: %d Rooms: %d\n\n", player.floorLoc + 1, branch, delCounter);
	printf("HP: ");
	for (int i = 0; i < player.maxHealth; i++)
	{
		printf("%c", (player.health > i ? 47 : 46));
	}
	printf("  %d/%d", player.health, player.maxHealth);
}