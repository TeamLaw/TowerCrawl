/*DrawEnviroment.c
Team Law
TowerCrawl
Programmers: Kyle Law, Jesse Sabatini, Andrew Neumann, Joe H
*/

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
	printf("\nBranch: %d Rooms: %d Floor: %d\n\n", branch, delCounter, location + 1);
	printf("HP: ");
	for (int i = 0; i < player.maxHealth; i++)
	{
		printf("%c", (player.health > i ? 47 : 46));
	}
	printf("  %d/%d", player.health, player.maxHealth);
}

void ShowPlayerStats()
{
	system("cls");
	printf("Player's Damage: %d \n", player.damage);
	printf("Player's Current Health: %d \n", player.health);
	printf("Player's Max Health: %d \n", player.maxHealth);
	printf("Player's Current Level: %d \n", player.level);
	printf("Player: *");
	printf("                 _A_ \n");
	printf("                / | \\ \n");
	printf("               |.-=-.| \n");
	printf("               )\\_|_/( \n");
	printf("            .=='\\   /`==. \n");
	printf("          .'\\   (`:')   /`. \n");
	printf("        _/_ |_.-' : `-._|__\\_ \n");
	printf("       <___>'\\    :    /`<___> \n");
	printf("       /  /   >=======<  /  / \n");
	printf("     _/ .'   /  ,-:-.  \\/=,' \n");
	printf("    / _/    |__/v^v^v\\__) \\ \n");
	printf("    \\(\\)     |V^V^V^V^V|\\_/ \n");
	printf("     (\\\\     \\`---|---'/ \n");
	printf("       \\\\     \\-._|_,-/ \n");
	printf("        \\\\     |__|__| \n");
	printf("         \\\\   <___X___> \n");
	printf("          \\\\   \\..|../ \n");
	printf("           \\\\   \\ | / \n");
	printf("            \\\\  /V|V\\ \n");
	printf("            \ \\|/  |  \\ \n");
	printf("              '--' `--` \n");
	_getch();

	drawRoom(player.roomLoc);
	drawInfo();
	if (player.roomLoc->enemy.health) { drawEntities((COORD){ 0,0 }, player.roomLoc->enemy.coord, player.roomLoc->enemy.marker); }
	drawEntities((COORD) { 0, 0 }, player.coord, player.marker);

	return 0;
}