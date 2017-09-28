
/*DrawEnviroment.c
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
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

/*drawEntities(COORD oldCoord, COORD coord, char marker)
Moves the cursor to the old coord and deletes the marker and reprints the marker at the new coord location
Parameters:
oldCoord - location of the entity's old position
coord - location of where the entity moved
marker - char to print on screen
Returns:
none
Programmer: Law
*/
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
	printf("Player's Current Level: %d \n\n", player.level);

	displayInventory(&player.inventory, invSizeLimit, 1);
	
	_getch();
	reDraw('r');
	reDraw('c');
	reDraw('n');
	reDraw('e');
	reDraw('p');

	return 0;
}

int displayInventory(struct Item * items, int size, int check)
{
	int count = 0;
	if (size) { printf("\n=%s=%s=\n\n", (check ? player.name : "NPC"), (check ? "Inventory" : "Merchandise")); }
	else { printf("\nWould you like to stay a night and rest?\n\n"); }

	for (int i = 1; i <= size; i++)
	{
		if (items->value)
		{
			printf("[ ] %s - value: %d\n\n", items->name, items->value);
			count++;
		}
		items++;
	}

	return count;
}

void reDraw(char draw)
{
	switch (draw)
	{
	case 'c':
		drawEntities((COORD) { 0, 0 }, player.coord, player.marker);
		break;
	case 'e':
		if (player.roomLoc->enemy.health > 0) { drawEntities((COORD) { 0, 0 }, player.roomLoc->enemy.coord, player.roomLoc->enemy.marker); }
		break;
	case 'n':
		if (floorStart == player.roomLoc)
		{
			drawEntities((COORD) { 0, 0 }, innkeeper.coord, innkeeper.marker);
			drawEntities((COORD) { 0, 0 }, blacksmith.coord, blacksmith.marker);
			drawEntities((COORD) { 0, 0 }, shopkeeper.coord, shopkeeper.marker);
		}
		break;
	case 'p':
		if (player.roomLoc->isPortal) { drawEntities((COORD) { 0, 0 }, player.roomLoc->portal.coord, player.roomLoc->portal.marker); }
		break;
	case 'r':
		drawRoom(player.roomLoc);
		drawInfo();
		drawLegend();
		break;
	}
}




/*printf("King %s\n", player.name);
printf("                  _A_ \n");
printf("                 / | \\ \n");
printf("                |.-=-.| \n");
printf("                )\\_|_/( \n");
printf("             .=='\\   /`==. \n");
printf("           .'\\   (`:')   /`. \n");
printf("         _/_ |_.-' : `-._|__\\_ \n");
printf("        <___>'\\    :    /`<___> \n");
printf("        /  /   >=======<  /  / \n");
printf("      _/ .'   /  ,-:-.  \\/=,' \n");
printf("     / _/    |__/v^v^v\\__) \\ \n");
printf("     \\(\\)     |V^V^V^V^V|\\_/ \n");
printf("      (\\\\     \\`---|---'/ \n");
printf("        \\\\     \\-._|_,-/ \n");
printf("         \\\\     |__|__| \n");
printf("          \\\\   <___X___> \n");
printf("           \\\\   \\..|../ \n");
printf("            \\\\   \\ | / \n");
printf("             \\\\  /V|V\\ \n");
printf("              \\\|/  |  \\ \n");
printf(" ______________'--' `--`_________________ \n");*/