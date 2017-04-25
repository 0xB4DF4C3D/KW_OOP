#include "StudentManager.h"

#include <fstream>
#include <iostream>

#include "myString.h"

using namespace std;

// This function is only used in MusicListManipulator this file, and it opens the file safely.
void validFileOpen(fstream& stream, const char* fileName, int mode = 3) {
	stream.open(fileName, mode);
	
	// If it fails to open ...
	if (stream.fail()) {
		cerr << "Failed to open " << fileName << '.' << endl;
		cerr << "Program will be aborted." << endl;
		exit(EXIT_FAILURE);
	};
}

StudentManager::StudentManager(const char* fileName) {

	fstream inputFile;
	validFileOpen(inputFile, fileName);

	int numberOfEntry;

	// If the file structure is inappropriate for the following reasons:
	//		If the letter comes where the numbers should come.
	//		The range of values is too small or too large.
	// If so, the program will be aborted.
	try {
		// Gets the number of entries stored in the file.
		if(safeNumInput(inputFile, numberOfEntry, 0, INT_MAX))
			throw exception("[!] Error. Number of entry must be a positive number.");

		mStudentList = new Student[numberOfEntry];

		char name[Student::NAME_SIZE], mail[Student::MAIL_SIZE], phone[Student::PHONE_SIZE];
		int idNumber, age;

		char lineBuf[BUFSIZ];
		char *token;
		mNumberOfStudent = 0; // Verify the actual number of students.

		// Each line is searched and the data is read.
		for (int idx = 0; idx < numberOfEntry; idx++) {

			if (inputFile.eof())
				throw exception("[!] Error. Actual item is less than expected.");

			inputFile.getline(lineBuf, BUFSIZ);

			token = my_tok(lineBuf, " ");
			my_cpy(name, token);

			token = my_tok(NULL, " ");
			my_cpy(mail, token);

			token = my_tok(NULL, " ");
			my_cpy(phone, token);

			token = my_tok(NULL, " ");
			if (!validateNumeric(token))
				throw exception("[!] Error. idNumber must be a number.");
			idNumber = atoi(token);

			token = my_tok(NULL, " ");
			if (!validateNumeric(token))
				throw exception("[!] Error. age must be a number.");
			age = atoi(token);

			mStudentList[idx].setStudent(name, mail, phone, idNumber, age);
			mNumberOfStudent++;
		}

		if (!inputFile.eof())
			throw exception("[!] Error. Actual item is more than expected.");

	} catch (const exception& e) {
		cerr << e.what() << endl;
		cerr << "Program will be aborted." << endl;
		inputFile.close();
		exit(EXIT_FAILURE);
	}

	inputFile.close();
}


StudentManager::~StudentManager() {
	delete[] mStudentList;
}

void StudentManager::printOldestStudent() {
	int oldestStudentIdx = 0, oldestStudentAge = 0;
	for (int idx = 0; idx < mNumberOfStudent; idx++) {

		// Find the index of the oldest student.
		if (oldestStudentAge < mStudentList[idx].getAge()) {
			oldestStudentAge = mStudentList[idx].getAge();
			oldestStudentIdx = idx;
		}
	}
	mStudentList[oldestStudentIdx].print();
}

void StudentManager::printAll() {
	for (int idx = 0; idx < mNumberOfStudent; idx++) {
		cout << idx << ". "; mStudentList[idx].print();
	}
}
