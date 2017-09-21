#include <stdio.h>
#include "TowerCrawl.h"

void drawEncounters(struct Entity* ENTITY_ptr)
{
	system("cls");

	// display attributes (health, dmg,..) from struct Player
	printf("Health: (%d) ", ENTITY_ptr->health);
	printf("Damage: (%d) ", ENTITY_ptr->damage);
}

/*
 This function does what
*/
void gameLogic( struct Entity* player, struct Entity* entity, int choice )
{
	// newPlayer
	int healingPotionPower = 10;
	int swordDamage = 55;

	// game logic
	switch (choice)
	{
	case 1:
		printf("[-] used the sword to inflict %d damage \n", swordDamage);
		player->health -= swordDamage;
		entity->health -= 15;
		break;

	case 2:
		printf("[-] used some healing lotion \n");

		// only add health if we don't go over max
		if (player->health + healingPotionPower <= player->maxHealth)
		{
			player->health += healingPotionPower;
		}
		else if (player->health == player->maxHealth)
		{
		}
		else if(player->health > player->maxHealth - healingPotionPower)
		{
			player->health = player->maxHealth;
		}

		break;
	default:
		break;
	}
}