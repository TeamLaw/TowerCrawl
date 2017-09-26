#include "TowerCrawl.h"

/*HandleEncounter(struct Player * Player, struct Sprite * Monster) 
	Will handle when a player encounters a monster
Parameters:
	Player - is the main player
	Monster- is the monster that the player is fighting
Returns:
	-1- if player dies
	0 - if player flees
	1 - if player wins the fight
*/
int handleEncounter(struct Player * Player, struct Sprite * Monster)
{
	drawEncounters(Player, Monster);
	enum PlayerChoice PC = Wait;

	while (1)
	{
		switch (getch() - 48)
		{
			//If the player hits "1" the player attacks
		case 1:
			PC = Attack;
			gameLogic(Player, Monster, PC);
			break;

			//If the player hits "2" the player uses a healing potion
		case 2:
			PC = Use_Potion;
			gameLogic(Player, Monster, PC);
			break;

			//If the player hits "3" the player waits
		case 3:
			PC = Wait;
			gameLogic(Player, Monster, PC);
			break;

			//If the player hits "7" the player cheats
		case 7:
			PC = Cheat;
			gameLogic(Player, Monster, PC);
			break;

		//Flee
		case 9:
			return 0;
			break;
		}

		if (Player->health <= 0)
		{
			printf("You dead!");
			return -1;
		}
		else if (Monster->health <= 0)
		{
			return 1;
		}


		drawEncounters(Player,Monster);
	}
}