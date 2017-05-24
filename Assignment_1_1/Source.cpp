#include <iostream>
#include <istream>
#include <cmath>
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

	int colSize;
	int rowSize;

	do { // Verification of input values.

		cout << "N: ";
		// The cin stream accepts only one number from 1 to INT_MAX.
		if (!safeIntInput(cin, rowSize, 1, INT_MAX)) {
			if (rowSize % 2 == 1) // Also check for oddness.
				break;
			else
				cerr << "[!] Input must be odd." << endl;
		}
	} while (true);

	// Process the rows as much as the input size.
	for (int i = 0; i < rowSize; i++) {

		// Padding on the left hand side.
		// Padding is implemented with abs(colSize / 2 - i) * 2 spaces.
		for (int j = 0; j < abs(rowSize / 2 - i) * 2; j++)
			cout << ' ';

		// The number of numbers in the ith row is rowSize - abs(rowSize / 2 - i) * 2.
		colSize = rowSize - abs(rowSize / 2 - i) * 2;

		// The value of the jth column of the ith row is calculated as (colSize / 2) - abs((colSize / 2) - j).
		for (int j = 0; j < colSize; j++)
			cout << (colSize / 2) - abs((colSize / 2) - j) << ' ';

		cout << endl;
	}

	return EXIT_SUCCESS;
}