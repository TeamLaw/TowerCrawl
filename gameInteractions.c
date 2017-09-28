/*gameInteractions.c
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
*/
#include "TowerCrawl.h"


//DrawEncounters will display the the health of both the monster and the player
void drawEncounters(struct Enemy * Monster)
{
	//#########################################
	//Graphics need to be added to their own  graphics text files
	//use pullGraphics(Filename);
	if (Monster->isBoss)
	{
		system("cls");
		printf("\n\n");
		printf("Brosifv Stalin spits on your Democracy! \n");
		printf("Brosifv Stalin's Health: %d\n\n", Monster->health);
		printf("                !#########       # \n");
		printf("              !########!          ##! \n");
		printf("           !########!               ### \n");
		printf("        !##########                  #### \n");
		printf("      ######### #####                ###### \n");
		printf("       !###!      !####!              ###### \n");
		printf("         !           #####            ######! \n");
		printf("                       !####!         ####### \n");
		printf("                          #####       ####### \n");
		printf("                            !####!   #######! \n");
		printf("                               ####!######## \n");
		printf("           ##                    ########## \n");
		printf("         ,######!           !############# \n");
		printf("        ,#### ########################!####! \n");
		printf("      ,####'     ##################!'    ##### \n");
		printf("    ,####'            #######              !####! \n");
		printf("   ####'                                      ##### \n");
		printf("   ~##                                          ##~ \n\n");
		printf("Your health : %d\n", player.health);
		printf("\nWhat do you do ?\n");
		printf("\nAttack(1)\nUse Item(2)\nWait(3)\nFlee(9)\n");
	}
	else
	{
		system("cls");
		printf("\n\n");
		printf("A monster stands before you!\n");
		printf("Its health : %d\n\n", Monster->health);
		printf("        ______ \n");
		printf("       /---.__\\ \n");
		printf("      /       `\\ \n");
		printf("     | o     o  \\ \n");
		printf("   /'| .vvvvv.  |'\\ \n");
		printf("  / /| |     |  |  \\ \n");
		printf(" / /'| `^^^^^'  |/\\ \\ \n");
		printf(" ~   \\          |  \\ \\ \n");
		printf("      |         |    ~ \n");
		printf("      7        / \n");
		printf("   _ /    .    | \n");
		printf("____-|_/\\/_`--.|____ \n\n");
		printf("Your health : %d\n", player.health);
		printf("\nWhat do you do ?\n");
		printf("\nAttack(1)\nUse Item(2)\nWait(3)\nFlee(9)\n");
	}
}

/*
void gameLogic(struct Enemy* Monster, enum PlayerChoice PC)

Purpose: takes the players choice and caculates what both the player's
and monster's action and health will be.. 

Parameter 1: struct Enemy* Monster (this is a pointer to the Monster struct)

Parameter 2: enum PlayerChoice PC (this is a PlayerChoice of type enum, which 
essentially contains a list of aliases to values we can use in our logic)

Programmer: Joe, Law
*/

void gameLogic(struct Enemy* Monster, enum PlayerChoice PC )
{
	// temp Healing Potion power
	int check = 1;

	// Takes Player choice
	switch (PC)
	{
	case Attack:
		//Player does damage to the monster
		Monster->health -= player.damage;		
		break;

	case Use_Item:
		// only add health if we don't go over max
		check = inventoryInteraction(player.inventory, displayInventory(player.inventory, invSizeLimit, 1), 'O', 1);
		drawEncounters(Monster);
		break;
		//Cheating is for losers :/
	case Cheat:
		//Player gets full health
		player.health = player.maxHealth;
		//Monster dies
		Monster->health = 0;
		break;
	case Wait:
		break;
	}
	if (check) { MonsterAction(Monster); }
}

//Determines what the monster will do
void MonsterAction(struct Enemy* Monster)
{
	//can't do much if it is dead ... or can it?
	if (Monster->health <= 0)
	{
		player.exp += Monster->exp;

		int experience = player.exp / 100, counter = 0;
		while (experience) { 
			counter++; experience /= 2; 
		}
		player.level = counter + 1;
		player.money += Monster->money;
	}
	else
	{
		//Monster attacks player
		player.health -= Monster->damage;
	}
	return;
}

void npcInteraction(struct NPC * npc, int invSize)
{
	int invPrinted = 0;

	system("cls");
	printf("Hello %s,\nWelcome to my %s\n\n", player.name, (invSize ? "Shop" : "Inn"));

	if (invSize)
	{
		printf("(1) Buy\n(2) Sell\n(3) Exit\n");

	REDOSHOP:
		switch (_getch())
		{
		case '1':
			printf("\n$: %d\n", player.money);
			invPrinted = displayInventory(&npc->merchandise, invSize, 0);
			printf("\nPress (e) to Exit");
			inventoryInteraction(&npc->merchandise, invPrinted, npc->marker, 0);
			break;
		case '2':
			printf("\n$: %d\n", player.money);
			invPrinted = displayInventory(&player.inventory, invSizeLimit, 1);
			printf("\nPress (e) to Exit");
			inventoryInteraction(&player.inventory, invPrinted, player.marker, 0);
			break;
		case '3':
			break;
		default:
			goto REDOSHOP;
		}
	}
	else
	{
		printf("(1) Stay the Night for $10\n(2) Exit\n");
	REDOINN:
		switch (_getch() - 48)
		{
		case 1:
			if (player.money >= 10) 
			{ 
				player.health = player.maxHealth; 
				player.money -= 10;
				printf("\nThank you for staying!\n");
			}
			else { printf("\nYou don't have enough money\n"); }
		case 2:
			break;
		default:
			goto REDOINN;
		}
	}

	player.coord.X = player.roomLoc->xSize / 2;
	player.coord.Y = player.roomLoc->ySize / 2;

	printf("\nI look forward to your next visit.");
	_getch();
	reDraw('r');
	reDraw('c');
	reDraw('n');
}
/*int inventoryInteraction(struct Items * items, int itemCount, char marker, int type)
Allows player to scroll through inventory and select an item
Parameters:
items - pointer to inventory array
itemCount - number of items in inventory
marker - checks whether player or npc inventory
type - type of interaction in which inventory is being accessed (1 for battle, 0 for shopping)
Returns:
int - if action was taken
Programmer: Law
*/
int inventoryInteraction(struct Items * items, int itemCount, char marker, int type)
{
	struct Item * item = items;
	int oldPos = 0, newPos = (type ? 29 : 11), loop = 1, count = 0, check = 0;

	drawEntities((COORD) { 0, 0 }, (COORD) { 1, newPos }, 'X');
	
	while (loop)
	{
		CONTINUE:
		switch (_getch())
		{
		case 'w':
			if (count)
			{
				do
				{
					item--;
					oldPos = newPos;
					newPos -= 2;
					count--;
					if (item->value) { drawEntities((COORD) { 1, oldPos }, (COORD) { 1, newPos }, 'X'); }
				} while (!item->value && count);
			}
			break;
		case 's':
			if (count < itemCount - 1)
			{
				do 
				{
					item++;
					oldPos = newPos;
					newPos += 2;
					count++;
					if (item->value) { drawEntities((COORD) { 1, oldPos }, (COORD) { 1, newPos }, 'X'); }
				} while (!item->value && count < itemCount - 1);
			}
			break;
		case '\r':
			check = inventoryProcess(item, marker, type, newPos);
			if (type) { loop = 0; }
			break;
		case 'e':
			moveCursor(0, 11 + (itemCount * 2));
			loop = 0;
			break;
		default:
			goto CONTINUE;
		}
	}
	return check;
}
/*int inventoryProcess(struct Item * item, char marker, int type, int newPos)
Processes the decision the player made on the displayed inventory
Parameters:
item - pointer to item selected
marker - checks whether player or npc inventory
type - type of interaction in which inventory is being accessed (1 for battle, 0 for shopping)
newPos - receives in coordinate to adjust
Returns:
int - if action was taken
Programmer: Law
*/
int inventoryProcess(struct Item * item, char marker, int type, int newPos)
{
	if (marker == 'O')
	{
		if (type)
		{
			moveCursor(0, 0);
			if (item->health) 
			{ 
				player.health = ((player.health + item->health) >= player.maxHealth ? player.maxHealth : player.health + item->health);
				item->value = 0;
				printf("Drank health potion");
				_getch();
				return 1;
			}
			else { printf("Oak: Now is not the time to use that!"); _getch(); }
		}
		else
		{
			player.money += item->value;
			moveCursor(2, 7);
			printf(" %d       ", player.money);
			item->value = 0;
			moveCursor(0, newPos);
			printf("    -Sold-                                                                                       ");
		}
	}
	else
	{
		if (player.money >= item->value)
		{
			if (!inventoryCheck(1))
			{
				player.money -= item->value;
				player.inventory[inventoryCheck(0)] = *item;
				moveCursor(2, 7);
				printf(" %d       ", player.money);
				moveCursor(0, newPos);
				printf("\n    -Thank you for your purchase-                                                 ");
			}
			else
			{
				moveCursor(0, newPos + 1);
				printf("    -Inventory is full-                                                 ");
			}
		}
		else
		{
			moveCursor(0, newPos + 1);
			printf("    -Not enough money-                                                 ");
		}
	}
	return 0;
}


int inventoryCheck(int type)
{
	int counter = 0;
	for (int i = 0; i < invSizeLimit; i++) { counter += (player.inventory[i].value ? 1 : 0); }

	if (type) { return (counter == invSizeLimit); }
	else { return counter; }
}

/*
void displayDeathScreen()

Purpose: Prints out ASCII art to the user upon losing all health.

Parameters: none

Programmer: Joe
*/
void displayDeathScreen()
{
	system("cls");

	printf("==================================================\n");
	printf("                 YOU HAVE DIED                    \n");
	printf("==================================================\n");
	printf("              ... \n");
	printf("            ;::::; \n");
	printf("          ;::::; :; \n");
	printf("        ;:::::'     :; \n");
	printf("       ;:::::;        ;. \n");
	printf("       ,::::: (*)  (*) ;             OOO\ \n");
	printf("       ::::::;   /\    ;            OOOOO\ \n");
	printf("       ;:::::;  ____   ;           OOOOOOO \n");
	printf("      ,;::::::; \__/ ;'         / OOOOOOOO \n");
	printf("    ;:::::::::`. ,,,;.         /  / DOOOOOO \n");
	printf("  .';:::::::::::::::::;,      /  /     DOOOO \n");
	printf(" ,::::::;::::::;;;;::::;,    /  /        DOOO \n");
	printf(";`::::::`'::::::;;;:::::  ,#/  /          DOOO \n");
	printf(":`:::::::`;::::::;;:::  ;::#  /            DOOO \n");
	printf("::`:::::::`;::::::::  ;::::# /              DOO \n");
	printf("`:`:::::::`;::::::  ;::::::#/               DOO \n");
	printf(" :::`:::::::`;;  ;:::::::::##                OO \n");
	printf(" ::::`:::::::`;::::::::;:::#                OO \n");
	printf(" `:::::`::::::::::::;'`:;::#                O \n");
	printf("  `:::::`::::::::;'  /  / `:# \n");
	printf("   ::::::`:::::;'   /  /   `# \n");
	_getch();
	return;
}