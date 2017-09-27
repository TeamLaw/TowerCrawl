/*gameInteractions.c
Team Law
TowerCrawl
Programmers: Kyle Law, Jesse Sabatini, Andrew Neumann, Joe H
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
		printf("You have 43 potions.\n");
		printf("\nWhat do you do ?\n");
		printf("\nAttack(1)\nUse Potion(2)\nWait(3)\nFlee(9)\n");
	}
	else
	{
		system("cls");
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
		printf("You have 43 potions.\n");
		printf("\nWhat do you do ?\n");
		printf("\nAttack(1)\nUse Potion(2)\nWait(3)\nFlee(9)\n");
	}
}


//GameLogic takes the players choice and caculates what both the player's
//and monster's action and health will be.

void gameLogic(struct Enemy* Monster, enum PlayerChoice PC )
{
	// temp Healing Potion power
	int healingPotionPower = 25;

	// Takes Player choice
	switch (PC)
	{
	case Attack:

		//Player does damage to the monster
		Monster->health -= player.damage;		

		//Monsters turn
		MonsterAction(Monster);

		break;

	case Use_Potion:
		// only add health if we don't go over max
		if (player.health + healingPotionPower <= player.maxHealth)
		{
			player.health += healingPotionPower;
		}
		else if (player.health == player.maxHealth)
		{
		}
		else if (player.health > player.maxHealth - healingPotionPower)
		{
			player.health = player.maxHealth;
		}
		//Monsters turn
		MonsterAction(Monster);
		break;

		//Cheating is for losers :/
	case Cheat:
		//Player gets full health
		player.health = player.maxHealth;
		//Monster dies
		Monster->health = 0;
		break;

	case Wait:
		//Monsters turn
		MonsterAction(Monster);
		break;
	}
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
	}
	else
	{
		//Monster attacks player
		player.health -= Monster->damage;
	}
	return;
}


// adding module for death screen animation
// adding module for death screen animation
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