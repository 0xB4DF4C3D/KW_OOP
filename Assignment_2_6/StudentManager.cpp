#include "StudentManager.h"

#include <fstream>
#include <iostream>

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

StudentManager::StudentManager(char *fileName) {
	fstream inputFile;

	validFileOpen(inputFile, fileName);

	char *token;
	char lineBuf[BUFSIZ];

	while (inputFile.getline(lineBuf, BUFSIZ)) {
		Student newStudent;
		
		token = my_tok(lineBuf, " ");	// Extract Day value.
		newStudent.setDay(token);

		token = my_tok(NULL, " ");		// Extract Name value.
		newStudent.setName(token);

		token = my_tok(NULL, " ");		// Extract Score value.
		newStudent.setScore(atoi(token));
		
		// Push new student on the appropriate day according to the student's day of the week.
		switch (newStudent.getDay()) {
		case Student::Days::WED:
			mWed.pushBack(newStudent);
			break;
		case Student::Days::THU:
			mThu.pushBack(newStudent);
			break;
		case Student::Days::FRI:
			mFri.pushBack(newStudent);
			break;
		case Student::Days::NON:
			mNone.pushBack(newStudent);
			break;
		}
	}
	
	inputFile.close();
}


StudentManager::~StudentManager() {
}

void StudentManager::printItem(Student::Days day, OOP::SortKeys sortKey) {
	switch (day) {
	case Student::Days::WED:
		mWed.PrintTitle(static_cast<int>(sortKey));
		mWed.printAll(sortKey);
		break;
	case Student::Days::THU:
		mThu.PrintTitle(static_cast<int>(sortKey));
		mThu.printAll(sortKey);
		break;
	case Student::Days::FRI:
		mFri.PrintTitle(static_cast<int>(sortKey));
		mFri.printAll(sortKey);
		break;
	case Student::Days::NON:
		mNone.PrintTitle(static_cast<int>(sortKey));
		mNone.printAll(sortKey);
		break;
	}
}
