#include <iostream>
#include <fstream>
#include <cstring>

#include "myString.h"

using namespace std;

int main() {

	ifstream inputFile("student.txt");
	
	if (inputFile.fail()) {
		cerr << "Failed to open file." << endl;
		cerr << "Program will be aborted." << endl;
		exit(EXIT_FAILURE);
	};

	// Read contents from student.txt.
	char originalString[BUFSIZ];
	inputFile.getline(originalString, BUFSIZ);
	inputFile.close();

	// Calculate the length of the reading.
	int originalStringLength = my_len(originalString);
	cout << "the length of string: " << originalStringLength << endl;

	// Copies the read contents to a new string buffer.
	char* copiedString = new char[originalStringLength+1];
	my_cpy(copiedString, originalString);
	cout << "the copied string : ";
	cout << copiedString << endl;
	delete[] copiedString;

	// Separate the read contents with a space.
	cout << "the result of truncating string (delimeter is ' ') : " << endl;
	char* token = my_tok(originalString, " ");
	do {
		cout << token << endl;
		token = my_tok(NULL, " ");
	} while (token != NULL);
	
	
	return EXIT_SUCCESS;
}