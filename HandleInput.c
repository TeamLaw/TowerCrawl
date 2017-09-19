int handleInput(void)
{
	char playerInput[50];
	scanf("%s", playerInput);

	for (int i = 0; playerInput[i]; i++) 
	{

		playerInput[i] = tolower(playerInput[i]);

		if (playerInput == '1' || playerInput == "one" ||  playerInput == "fight" || playerInput == "attack")
		{
			return 1;
		}
		else if (playerInput == '2' || playerInput == "two" || playerInput == "use item" || playerInput == "use potion" ||
			playerInput == "use" || playerInput == "item" || playerInput == "potion")
		{
			return 2;
		}
		else if (playerInput == '9' || playerInput == "nine" || playerInput == "flee" || playerInput == "run" || playerInput == "run away")
		{
			return 9;
		}
	}
}


