#include "TowerCrawl.h"


//DrawEncounters will display the the health of both the monster and the player
void drawEncounters(struct Player * Player, struct Enemy * Monster)
{
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
		printf("Your health : %d\n", Player->health);
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
		printf("Your health : %d\n", Player->health);
		printf("You have 43 potions.\n");
		printf("\nWhat do you do ?\n");
		printf("\nAttack(1)\nUse Potion(2)\nWait(3)\nFlee(9)\n");
	}
}


//GameLogic takes the players choice and caculates what both the player's
//and monster's action and health will be.

void gameLogic( struct Player* Player, struct Sprite* Monster, enum PlayerChoice PC )
{
	// temp Healing Potion power
	int healingPotionPower = 25;

	// Takes Player choice
	switch (PC)
	{
	case Attack:

		//Player does damage to the monster
		Monster->health -= Player->damage;		

		//Monsters turn
		MonsterAction(Player, Monster);

		break;

	case Use_Potion:
		// only add health if we don't go over max
		if (Player->health + healingPotionPower <= Player->maxHealth)
		{
			Player->health += healingPotionPower;
		}
		else if (Player->health == Player->maxHealth)
		{
		}
		else if (Player->health > Player->maxHealth - healingPotionPower)
		{
			Player->health = Player->maxHealth;
		}
		//Monsters turn
		MonsterAction(Player, Monster);
		break;

		//Cheating is for losers :/
	case Cheat:
		//Player gets full health
		Player->health = Player->maxHealth;
		//Monster dies
		Monster->health = 0;
		break;

	case Wait:
		//Monsters turn
		MonsterAction(Player, Monster);
		break;
	}
}

//Determines what the monster will do
void MonsterAction(struct Player* Player, struct Sprite* Monster)
{
	//can't do much if it is dead ... or can it?
	if (Monster->health <= 0)
	{
		Player->exp += Monster->exp;

		// determine if level up
		// after one of the above things has happened, let's determine if a level up is warranted
		if (Player->exp >= 100 && Player->exp < 200)
		{
			// level up to level 2
			Player->level = 2;
		}
		else if (Player->exp >= 200 && Player->exp < 400)
		{
			// level up to level 3
			Player->level = 3;
		}
		else if (Player->exp >= 400 && Player->exp < 800)
		{
			// level up to level 4
			Player->level = 4;
		}
		else if (Player->exp >= 800)
		{
			// level up to level 5
			Player->level = 5;
		}
	}
	else
	{
		//Monster attacks player
		Player->health -= Monster->damage;
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
	printf("                   ... \n");
	printf("                 ;::::; \n");
	printf("               ;::::; :; \n");
	printf("             ;:::::'   :; \n");
	printf("            ;:::::;      ;. \n");
	printf("	   ,:::::'        ;             OOO\ \n");
	printf("	   ::::::;        ;            OOOOO\ \n");
	printf("	   ;:::::;        ;           OOOOOOOO \n");
	printf("	  ,;::::::;      ;'           / OOOOOOO \n");
	printf("	;:::::::::`. ,,,;.           /  / DOOOOOO \n");
	printf("  .';:::::::::::::::::;,        /  /     DOOOO \n");
	printf(" ,::::::;::::::;;;;::::;,      /  /        DOOO \n");
	printf(";`::::::`'::::::;;;:::::::  ,#/  /          DOOO \n");
	printf(":`:::::::`;::::::;;:::::: ;::#  /            DOOO \n");
	printf("::`:::::::`;::::::::::  ;::::# /              DOO \n");
	printf("`:`:::::::`;::::::::  ;::::::#/               DOO \n");
	printf(" :::`:::::::::`;;  ;:::::::::##                OO \n");
	printf(" ::::`:::::::::`;::::::::;:::#                OO \n");
	printf(" `:::::`::::::::::::;'`:;::#                O \n");
	printf("  `:::::`::::::::::;'  /  / `:# \n");
	printf("   ::::::`:::::::;'   /  /   `# \n");
}