/*Handle Encounter returns
0 if you die
1 if you stay alive
*/
int handleEncounter(struct Entity * monster_entity)
{
	drawEncounterGUI(&monster_entity);
	while (1)
	{
		int input = receiveInput();
		if (input = 9)
		{
			printf("Bravely run away!");
			return 1;
		}
		gameLogic(input, &monster_entity);
		if (newPlayer.health <= 0)
		{
			printf("You dead!");
			return 0;
		}
		else if ((*(monster_entity)).health <= 0)
		{
			return 1;
		}

		drawEncounterGUI(&monster_entity);

	}
}
