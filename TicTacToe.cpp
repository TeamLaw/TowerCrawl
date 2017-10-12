#include "TicTacToe.h"
#include <stdio.h>
#include <iostream>

//extern void TicTacToe::playGame();
static char ticTacToeGrid[3][3];

void TicTacToe::playGame()
{
	/* PRINT THE LEGEND AND CURRENT STATUS OF THE GAME */
	int position = 0;
	char marker = 0;
	char flag = 0;

	while (1)
	{
		print_the_grid();

		printf("Enter a position: ");
		scanf_s(" %d", &position);
		//std::cin >> position;

		printf("Are you 'X' or 'O': ");
		scanf_s(" %c", &marker);
		//std::cin >> marker;

		// make a  move
		what_is_your_play(marker, position);

		// check if we have a winner
		flag = did_someone_win();

		if (flag != 0)
		{
			system("cls");
			printf("WINNER: %c \n", flag);
			break;
		}
	}
}


int TicTacToe::print_the_grid(void)
{
	// hard code values
	//grid[row#][column#]

	int initialBoardLayoutNumber = 1;

	printf("\nBoard Positions \n\n");

	// 
	// print out the lengend
	//
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++) // each column in the row
		{
			//printf("grid[%d][%d] -> %d", r, c, ticTacToeGrid[r][c]);

			if (c < 2)
			{
				printf(" %d |", initialBoardLayoutNumber++);
			}
			else
			{
				printf(" %d", initialBoardLayoutNumber++);
			}

		}
		if (r < 2)
			printf("\n-----------\n");
	}

	printf("\n\n");
	printf("\nCurrent Board Status \n\n");

	// 
	// print out current state of board
	//
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++) // each column in the row
		{
			//printf("grid[%d][%d] -> %d", r, c, ticTacToeGrid[r][c]);

			if (c < 2)
			{
				printf(" %c |", ticTacToeGrid[r][c]);
			}
			else
			{
				printf(" %c", ticTacToeGrid[r][c]);
			}

		}
		if (r < 2)
			printf("\n-----------\n");
	}

	printf("\n\n");

	return 1; // You'll need to change this
}


int TicTacToe::any_plays_left(void)
{
	// count each element of the array, 
	// if an element is a space ' ' (0x20), it is available,
	// else it is likely an X or O << these are not available spaces
	int choicesLeft = 0;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++) // each column in the row
		{
			if (ticTacToeGrid[r][c] == 0)
			{
				choicesLeft++;
			}
		}
	}

	return choicesLeft;
}


char TicTacToe::did_someone_win(void)
{
	char winner = -1;
	char X = 'X';
	char O = 'O';
	// o o o
	// - - -
	// - - -

	// do we have any winners across a row O O O for instance

	// for each row, check it
	// 
	// print out the lengend
	//
	for (int r = 0; r < 3; r++)
	{
		//check horizontals
		if (((ticTacToeGrid[r][0] == ticTacToeGrid[r][1]) && (ticTacToeGrid[r][0] == ticTacToeGrid[r][2])) && (ticTacToeGrid[r][0] == 'X'))
		{
			winner = 'X';
		}
		else if (((ticTacToeGrid[r][0] == ticTacToeGrid[r][1]) && (ticTacToeGrid[r][0] == ticTacToeGrid[r][2])) && (ticTacToeGrid[r][0] == 'O'))
		{
			winner = 'O';
		}
		// check verticals
		else if (((ticTacToeGrid[0][r] == ticTacToeGrid[1][r]) && (ticTacToeGrid[2][r] == ticTacToeGrid[0][r])) && (ticTacToeGrid[0][r] == 'X'))
		{
			winner = 'X'; // any position should be ok
		}
		else if (((ticTacToeGrid[0][r] == ticTacToeGrid[1][r]) && (ticTacToeGrid[2][r] == ticTacToeGrid[0][r])) && (ticTacToeGrid[0][r] == 'O'))
		{
			winner = 'O'; // any position should be ok
		}

		//////////////////////////////////

		//printf("\nnext row \n");

		// continue unless winner found
		if (winner != -1)
			return winner;
	}

	// check corners
	if ((ticTacToeGrid[0][0] == ticTacToeGrid[1][1] && ticTacToeGrid[0][0] == ticTacToeGrid[2][2]) && (ticTacToeGrid[0][0] == 'X'))
	{
		winner = 'X';
	}
	else if ((ticTacToeGrid[2][0] == ticTacToeGrid[1][1] && ticTacToeGrid[1][1] == ticTacToeGrid[0][2]) && (ticTacToeGrid[2][0] == 'O'))
	{
		winner = ticTacToeGrid[1][1];
	}
	else
	{
		system("cls");
		printf("NO WINNER! \n");
		return 0;
	}

	return winner;
}


int TicTacToe::what_is_your_play(char currentPlayer, int gridLocation)
{
	int counter = 1;
	int x = 0, y = 0;
	int foundIt = 0;

	//printf("what is ur play... %c \n", currentPlayer);

	// input validation
	if (currentPlayer != 'X' && currentPlayer != 'O')
	{
		system("cls");
		printf("Please enter either an 'X' or an 'O' \n");
		return -1;
	}

	// gridLocation range validation
	if (gridLocation < 1 || gridLocation > 9)
	{
		system("cls");
		printf("Please enter a grid location between 1 and 9 inclusive \n");
		return -1;
	}

	// gridLocation available validation
	// if user enters grid location 1, we need to make sure 
	// to find the value associated with grid[0][1] and see
	// if its empty, else invalid move.

	// calculate gridCoordinate, give gridLocation
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++) // each column in the row
		{
			if (counter == gridLocation)
			{
				x = r;
				y = c;
				foundIt = 1;
				break;
			}
			else
			{
				counter++;
			}
		}

		// if we found it, were done
		if (foundIt)
			break;
	}

	//printf("Found it at %d,%d \n", x, y);

	// let's make sure this is an empty space
	if (ticTacToeGrid[x][y] == 0)
	{
		//printf("found empty spot, valid move \n");
		ticTacToeGrid[x][y] = currentPlayer;
		return 1;
	}
	else
	{
		system("cls");
		printf("invalid move.. alrdy taken.. try again \n");
		return 0;
	}
}
