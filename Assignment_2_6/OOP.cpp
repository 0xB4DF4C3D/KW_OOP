#include "OOP.h"

#include <iostream>
#include <functional>

using namespace std;

inline void swap(Student& a, Student& b) {
	Student temp = a;
	a = b;
	b = temp;
}


void OOP::pushBack(Student newStudent) {
	if (mStudentSize >= MAX_STUDENT) {
		cerr << "[!] Errror. number of student must be in " << 0 << " ~ " << MAX_STUDENT << endl;
		throw invalid_argument("invalid argument in OOP::pushBack");
	}
	mStudents[mStudentSize++] = newStudent;
}

void OOP::printAll(SortKeys sortKey) {

	// Function wrapper are used to correspond to various sort keys.
	function<bool(int)> sortCustom;

	// Since the keys actually differ in how they compare, 
	// this part (such as a string or number) must be defined before sorting.

	// Here I have simplified code by using an anonymous function called lambda, one of the features of C ++ 11.
	switch (sortKey) {
	case SortKeys::NAME:
		sortCustom = [&](int j) {return my_cmp(mStudents[j].getName(), mStudents[j - 1].getName()) < 0; };
		break;

	case SortKeys::SCORE:
		sortCustom = [&](int j) {return mStudents[j].getScore() > mStudents[j - 1].getScore(); };
		break;
	}

	// sort with the custom sort method specified above.
	for (int i = 0; i < mStudentSize - 1; i++)
		for (int j = mStudentSize - 1; j > i; j--)
			if (sortCustom(j))
				swap(mStudents[j], mStudents[j - 1]);

	// Determine correspoding day using one of studetns.
	char day[16];

	switch (mStudents[0].getDay()) {
	case Student::Days::WED:
		my_cpy(day, "수");
		break;
	case Student::Days::THU:
		my_cpy(day, "목");
		break;
	case Student::Days::FRI:
		my_cpy(day, "금");
		break;
	case Student::Days::NON:
		my_cpy(day, "미수강");
		break;
	}


	for (int i = 0; i < mStudentSize; i++)
		cout << day << " " << mStudents[i].getName() << " " << mStudents[i].getScore() << endl;

}
