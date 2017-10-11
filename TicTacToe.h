#pragma once
class TicTacToe
{

public:	
	// public functions go here >>
	static void playGame();
	static int print_the_grid(void);
	static int any_plays_left(void);
	static char did_someone_win(void);
	static int what_is_your_play(char currentPlayer, int gridLocation);	
};