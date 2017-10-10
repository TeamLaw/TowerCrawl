/*HandleEncounter.c
Team Law
TowerCrawl
Programmers: Kyle, Jesse, Andrew, Joe
*/

#include "TowerCrawl.h"

/*
HandleEncounter(struct Player * Player, struct Sprite * Monster)
Will handle when a player encounters a monster
Parameters:
Player - is the main player
Monster- is the monster that the player is fighting
Returns:
-1- if player dies
0 - if player flees
1 - if player wins the fight
*/
int handleEncounter(Enemy * Monster)
{
	drawEncounters(Monster);
	enum PlayerChoice PC = Wait;

	while (1)
	{
		switch (_getch())
		{
			//If the player hits "1" the player attacks
		case '1':
			PC = Attack;
			gameLogic(Monster, PC);
			break;

			//If the player hits "2" the player uses a healing potion
		case '2':
			PC = Use_Item;
			gameLogic(Monster, PC);
			break;

			//If the player hits "3" the player waits
		case '3':
			PC = Wait;
			gameLogic(Monster, PC);
			break;

			//If the player hits "7" the player cheats
		case '7':
			PC = Cheat;
			gameLogic(Monster, PC);
			break;

			//Flee
		case '9':
			return 0;
			break;

		}

		if (player.health <= 0)
		{
			printf("You dead!");
			return -1;
		}
		else if (Monster->health <= 0)
		{
			// give player gains experience, this gaining levels?
			return 1;
		}

		drawEncounters(Monster);
	}
}
