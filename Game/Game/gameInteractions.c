#include <stdio.h>

void drawEncounters(struct Entity* ENTITY_ptr)
{
	system("cls");

	// display attributes (health, dmg,..) from struct Player
	printf("Health: (%d) ", ENTITY_ptr->health);
	printf("Damage: (%d) ", ENTITY_ptr->damage);
}

void gameLogic(int choice, struct Entity* MONSTER_ptr)
{
	// newPlayer
	int healingPotionPower = 10;
	int swordDamage = 55;

	// game logic
	switch (choice)
	{
	case 1:
		printf("[-] used the sword to inflict %d damage \n", swordDamage);
		newPlayer.health -= swordDamage;
		break;
	case 2:
		printf("[-] used some healing lotion \n");

		// only add health if we don't go over max
		if (newPlayer.health + healingPotionPower <= newPlayer.maxHealth)
		{
			newPlayer.health += healingPotionPower;
		}
		else if (newPlayer.health == newPlayer.maxHealth)
		{
		}
		else if(newPlayer.health  > newPlayer.maxHealth - healingPotionPower)
		{
			newPlayer.health = newPlayer.maxHealth;
		}

		break;
	default:
		break;
	}
}