#include <stdio.h>
#include <conio.h>
#include "TowerCrawl.h"

/*Handle Encounter returns
0 if you die
1 if you stay alive
*/
int handleEncounter(struct Entity * player, struct Entity * entity)
{
	//drawEncounterGUI(entity);
	while (1)
	{
		switch (getch() - 48)
		{
		case 1:
			//gameLogic(player, entity);
			break;

		case 2:
			break;

		case 9:
			printf("Bravely run away!");
			return 0;
			break;
		}

		if (player->health <= 0)
		{
			printf("You dead!");
			return 0;
		}
		else if (entity->health <= 0)
		{
			return 1;
		}

		//drawEncounterGUI(entity);
	}
}