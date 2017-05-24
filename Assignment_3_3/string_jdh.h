#pragma once

#include <cstdlib>

int my_len(char* str1);							// Calculate the length of the string.
char* my_cpy(char* str2, char* str1);			// Copy str1 string value to str2.
char* my_tok(char* str1, char* delimiters);		// Tokenize str1 as delimiters.
int my_cmp(const char* str1, const char* str2);	// Compare str1 and str2.

bool validateNumeric(const char* numericString);	// Verify that the given C style string is only a number.

// Receives input from a stream and verifies that it is a number.
// Further scope validation.
// It also verifies that several values come in at once.
template<typename T1, typename T2>
bool safeNumInput(T1 &stream, T2& i, long min, long max, bool onlyGetOne = true) {
	stream >> i;

	if (cin.fail() || i < min || i > max) { // Invalid input or out of range.
		cerr << "[!] Error. Input must be in " << min << "~" << max << endl;
		stream.clear(); stream.ignore(INT_MAX, '\n'); // Initialize the stream.
		return EXIT_FAILURE;
	}

	if (onlyGetOne) { // If the onlyGetOne flag is on
		char c;
		while (stream.get(c) && c != '\n') { // Check for additional input after.
			if (!isspace(c)) {
				cerr << "[!] Error. There are strange values behind." << endl;
				stream.clear(); stream.ignore(INT_MAX, '\n'); // Initialize the stream.
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

// It takes input from stream and assigns it securely to C style string.
// It returns a failure if the given string buffer size is insufficient, as well as the length.
template<typename T1>
bool safeCstrInput(T1 &stream, char cStr[], int min, int max) {

	stream.getline(cStr, max);

	if (cin.fail() || my_len(cStr) < min) { // Invalid input or out of range.
		cerr << "[!] Input length must be in " << min << "~" << max << endl;
		stream.clear();

		if (my_len(cStr) >= min)
			stream.ignore(INT_MAX, '\n'); // Initialize the stream.
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}