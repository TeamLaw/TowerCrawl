
#include "HandleEncounter.h"

//DrawEncounters will display the the health of both the monster and the player
void drawEncounters(struct Player * Player, struct Sprite * Monster)
{
	system("cls");
	printf("A monster stands before you!\n");
	printf("Its health : %d\n\n",Monster->health);
	printf("Your health : %d\n",Player->health);
	printf("You have 43 potions.\n");
	printf("What do you do ?\n");
	printf("Attack(1) - Use Potion(2) - Wait(3) - Flee(9)\n");
}

//GameLogic takes the players choice and caculates what both the player's
//and monster's action and health will be.
void gameLogic( struct Player* Player, struct Sprite* Monster,enum PlayerChoice PC )
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
		printf("[-] used some healing lotion \n");

		// only add health if we don't go over max
		if (Player->health + healingPotionPower <= Player->maxHealth)
		{
			Player->health += healingPotionPower;
		}
		else if (Player->health == Player->maxHealth)
		{
		}
		else if(Player->health > Player->maxHealth - healingPotionPower)
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

	}
	else
	{
		//Monster attacks player
		Player->health -= Monster->damage;
	}
	return;
}