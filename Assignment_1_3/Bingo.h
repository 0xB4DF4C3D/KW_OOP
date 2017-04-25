#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#pragma once
class Bingo {
public:
	Bingo(int _boardSize, char *_name);
	~Bingo();

protected:
	void swap(int& a, int& b);

private:
	int **board;	// A two-dimensional array that stores board state.
	int boardSize;
	char *name;		// The name of the board owner.
	int shuffle();	// Shuffle board numbers.

public:
	int callRandomNumber();	// Pick random numbers for AI.
	bool checkBingo();		// Check whether the current board status is bingo.
	void draw();				// Output current board status.
	void start();			// Initialize the board, mix and draw.

	// Check the box corresponding to cardNumber.
	// If peekFlag is true, do not check it, but make sure it is already checked.
	bool turnCard(int cardNumber, bool peekFlag = false);

};

