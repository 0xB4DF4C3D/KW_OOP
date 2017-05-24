#include <iostream>
#include "Bingo.h"

using namespace std;

template<typename T1> // Templates for various streams.
bool safeIntInput(T1 &stream, int& i, int min, int max, bool onlyGetOne = true) {
	stream >> i;
	if (cin.fail() || i < min || i > max) { // Invalid input or out of range.
		cerr << "[!] Input must be in " << min << "~" << max << endl;
		stream.clear(); stream.ignore(INT_MAX, '\n'); // Initialize the stream.
		return EXIT_FAILURE;
	}
	if (onlyGetOne) { // If the onlyGetOne flag is on
		char c;
		while (stream.get(c) && c != '\n') { // Check for additional input after.
			if (!isspace(c)) {
				cerr << "[!] There are strange values behind." << endl;
				stream.clear(); stream.ignore(INT_MAX, '\n'); // Initialize the stream.
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

int main() {

	Bingo userBoard(5, "user");
	Bingo computerBoard(5, "computer");

	int cardNumber;

	// Set the cards and mix them.
	userBoard.start();
	computerBoard.start();

	// Use & instead of && to calculate all expressions.
	// Repeat the block below until someone becomes a bingo.
	while (!userBoard.checkBingo() & !computerBoard.checkBingo()) {

		// User part start.. -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		do { // Continue input until the input is valid.
			cout << "Call a number (1~25): ";
			if (safeIntInput(cin, cardNumber, 1, 25)) {
				cout << endl;
				continue;
			}

			if ( // Use && to avoid duplicate error notifications.
				!userBoard.turnCard(cardNumber) &&
				!computerBoard.turnCard(cardNumber)
				)
				break;
			else
				cout << endl;
		} while (true);



		userBoard.draw();
		computerBoard.draw();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
		// User part end.. -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		// When the user's turn is over, check if it is bingo.
		if (userBoard.checkBingo() | computerBoard.checkBingo())
			break;

		// Computer part start.. -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		cardNumber = computerBoard.callRandomNumber();
		cout << "Computer called " << cardNumber << endl << endl;

		( // Use && to avoid duplicate error notifications.
			!userBoard.turnCard(cardNumber) &&
			!computerBoard.turnCard(cardNumber)
			);

		userBoard.draw();
		computerBoard.draw();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
		// Computer part end.. -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	}

	return EXIT_SUCCESS;
}