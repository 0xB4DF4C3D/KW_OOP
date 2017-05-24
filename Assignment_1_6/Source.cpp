#include <iostream>

using namespace std;

unsigned int getRectCases(unsigned int numberOfRect) {
	
	/*
	* When there are numberOfRect boxes,
	* the number of cases where two adjacent boxes are laid down is as follows.
	* First, if there is one box, it is one
	* And when there are two boxes, one is added and another is added.
	* That is, when there are n, it can be divided into small units.
	* In other words, it is Fibonacci.
	*/
	int a = 1, b = 1, c = 1;
	const unsigned int MOD = 1000;

	// Compute the Fibonacci using (a + b) mod n = (a mod n + b mod n)mod n, 
	// one of the properties of the modular operation.
	for (int i = 0; i < numberOfRect-1; i++) {
		c = (a + b) % MOD;
		a = b % MOD; b = c % MOD;
	}

	// Returns the result.
	return c;
}

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
	int numberOfRect; // A variable that receives the number of boxes.
	int numberOfCase; // Variable to receive the number of cases.

	while (true) { // Repeat until the appropriate value is entered.
		cout << "Test Case: ";

		// The number of cases must be between 1 and 20.
		if (safeIntInput(cin, numberOfCase, 1, 20))
			continue;
		cout << endl;
		break;
	}

	// Input numberOfCase times.
	for (int count = 0; count < numberOfCase; count++) {
		cout << "Input: ";
		
		// The number of boxes must be between 1 and 50.
		if (safeIntInput(cin, numberOfRect, 1, 500)) {
			count--;
			continue;
		}

		// Output the result.
		cout << "Output: " << getRectCases(numberOfRect) << endl << endl;
	}

	return EXIT_SUCCESS;
}