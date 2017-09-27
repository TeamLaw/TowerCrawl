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
	printf("\n\nRooms: %d Floor: %d\n\n", delCounter, location);
	printf("HP: %d/%d\n", player.health, player.maxHealth);
	printf("$: %d", player.money);
}

void drawLegend()
{
	printf("\n\n\n=LEGEND==========\n\n");
	printf(" O   %s\n", player.name);
	printf(" S   Shopkeeper\n");
	printf(" B   Blacksmith\n");
	printf(" I   Innkeeper\n");
	printf(" C   Chest\n");
	printf(" x   Monster\n");
	printf(" #   Boss\n");
	printf(" @   Portal\n");
}

void ShowPlayerStats()
{
	system("cls");
	printf("Player's Damage: %d \n", player.damage);
	printf("Player's Current Health: %d \n", player.health);
	printf("Player's Max Health: %d \n", player.maxHealth);
	printf("Player's Current Level: %d \n", player.level);
	_getch();

	drawRoom(player.roomLoc);
	drawInfo();
	drawLegend();
	if (player.roomLoc->enemy.health > 0) { drawEntities((COORD){ 0,0 }, player.roomLoc->enemy.coord, player.roomLoc->enemy.marker); }
	drawEntities((COORD) { 0, 0 }, player.coord, player.marker);

	return 0;
}