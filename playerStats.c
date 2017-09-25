#include "TowerCrawl.h"

void ShowPlayerStats(struct Player* newPlayer)
{
	printf("Player's Damage: %d \n", Player->damage);
	printf("Player's Current Health: %d \n", Player->health);
	printf("Player's Max Health: %d \n", Player->maxHealth);
	printf("Player's Current Level: %d \n", Player->level);

	return 0;
}