#include <iostream>
#include <fstream>

#include "myString.h"

using namespace std;

int main() {

	ifstream inputFile("input.txt");

	cout.setf(ios::fixed); // Set the decimal precision of the cout stream to 1.
	cout.precision(1);
	
	// Set the maximum number of characters to be read at once to 512.
	char lineBuf[BUFSIZ];


	int linesLengthSum = 0, lineCount = 0,
		longestLineLehgth = 0, longestLineIndex = 0;

	// Read each line.
	do {
		inputFile.getline(lineBuf, BUFSIZ);

		lineCount++;
		int currentLineLength = my_len(lineBuf);

		// Find the longest row.
		if (currentLineLength > longestLineLehgth) {
			longestLineLehgth = currentLineLength;
			longestLineIndex = lineCount;
		}

		linesLengthSum += currentLineLength;
		cout << lineBuf << " - " << currentLineLength << endl;
	} while (!inputFile.eof());

	cout << "The average length is " << static_cast<double>(linesLengthSum) / lineCount << endl;
	cout << "The longest line is line " << longestLineIndex << endl;

	return EXIT_SUCCESS;
}