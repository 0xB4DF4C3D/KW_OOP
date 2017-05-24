#include "Bingo.h"

using namespace std;


Bingo::Bingo(int _boardSizes, char *_name) : boardSize(_boardSizes), name(_name) {
	// Dynamically allocates a two-dimensional array of boardSize*boardSize size.
	board = new int*[boardSize];
	for (int i = 0; i < boardSize; i++)
		board[i] = new int[boardSize];

}


Bingo::~Bingo() {
	// Delete the array that was dynamically allocated.
	for (int i = 0; i < boardSize; i++)
		delete[] board[i];
	delete[] board;
}


void Bingo::swap(int& a, int& b) {
	// Just a function that exchanges two argument values.
	int temp;

	temp = a;
	a = b;
	b = temp;
}


int Bingo::shuffle() {
	// Set the random seed value.
	// Considering the case of initializing two objects at the same time,
	// Let's consider the name in addition.

	// If you want to be independent of name,
	// use memory addresses instead of name.
	srand((unsigned int)time(NULL) + (unsigned int)name);

	int boardSizePow = boardSize * boardSize;
	for (int i = boardSizePow - 1; i > 0; i--) {
		int j = rand() % (i + 1);	// Convert 2D to 1D for easy mixing.

		// If 0 < i < A*B when there is a [A][B] array, 
		// i / B is [][] and i % B is [].
		int rowA = i / boardSize; int rowB = i % boardSize;
		int colA = j / boardSize; int colB = j % boardSize;
		swap(board[rowA][colA], board[rowB][colB]);
	}

	return 0;
}


void Bingo::draw() {
	// Output the board owner.
	cout << "<" << name << " bingo board>" << endl;

	// Traverse all fields
	for (int row = 0; row < boardSize; row++) {
		for (int col = 0; col < boardSize; col++)
			if (board[row][col])
				cout << setw(2) << board[row][col] << ' ';
			else // If value of the corresponding field is zero.
				cout << setw(2) << '#' << ' '; // Output # instead of digits.
		cout << endl;
	}
	cout << endl;
}


bool Bingo::turnCard(int cardNumber, bool peekFlag) {
	// Find the card that matches cardNumber.
	for (int row = 0; row < boardSize; row++) {
		for (int col = 0; col < boardSize; col++) {
			if (board[row][col] == cardNumber) { // When the card is found.
				// If peekFlag is on, leave it alone.
				// If it is off, make it 0 (flip).
				board[row][col] = peekFlag ? board[row][col] : 0;
				return EXIT_SUCCESS;
			}
		}
	}
	if (!peekFlag)
		cerr << "[!] That card number is already called. " << endl;
	// If the card number is already called, it returns a failure.
	return EXIT_FAILURE;
}

int Bingo::callRandomNumber() {
	// Set the random seed value.
	// Considering the case of initializing two objects at the same time,
	// Let's consider the name in addition.
	srand((unsigned int)time(NULL) + (int)name);

	int cardNumberToTurn;

	do { // keep picking numbers until get a number not picked up yet.
		cardNumberToTurn = rand() % (boardSize * boardSize) + 1;
	} while (turnCard(cardNumberToTurn, true));

	return cardNumberToTurn; // Returns the new number.
}


bool Bingo::checkBingo() {
	int checkRow, checkCol;

	// Row check.
	for (int row = 0; row < boardSize; row++) {
		checkRow = 0; // Set the checkRow value to 0
		// and add the values of all the columns in each row.
		for (int col = 0; col < boardSize; col++)
			checkRow += board[row][col];

		// If checkRow is 0, 
		// then all the columns in the row are 0,
		// meaning that all of them are checked.
		if (checkRow == 0) {
			cout << name << " BINGO!!" << endl;
			return true;
		}
	}

	// Column check. It is as above.
	for (int col = 0; col < boardSize; col++) {
		checkCol = 0;
		for (int row = 0; row < boardSize; row++)
			checkCol += board[row][col];
		if (checkCol == 0) {
			cout << name << " BINGO!!" << endl;
			return true;
		}
	}

	return false;
}


void Bingo::start() {
	int idx = 1;

	// Assign a number from 1 to each board space.
	for (int row = 0; row < boardSize; row++)
		for (int col = 0; col < boardSize; col++)
			board[row][col] = idx++;

	// And mix and output.
	shuffle();
	draw();
}
