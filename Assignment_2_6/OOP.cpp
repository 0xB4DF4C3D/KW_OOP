#include "OOP.h"
#include <iostream>

using namespace std;

inline void swap(Student& a, Student& b) {
	Student temp = a;
	a = b;
	b = temp;
}


void OOP::pushBack(Student newStudent) {
	if (mStudentSize >= MAX_STUDENT)
		throw std::out_of_range("error.");
	mStudents[mStudentSize++] = newStudent;
}

void OOP::printAll(SortKeys sortKey) {

	switch (sortKey) {
	case SortKeys::NAME:
		for (int i = 0; i < mStudentSize - 1; i++)
			for (int j = mStudentSize - 1; j > i; j--)
				if (my_cmp(mStudents[j].getName(), mStudents[j - 1].getName()) > 0)
					swap(mStudents[j], mStudents[j - 1]);
		break;
	case SortKeys::SCORE:
		for (int i = 0; i < mStudentSize - 1; i++)
			for (int j = mStudentSize - 1; j > i; j--)
				if (mStudents[j].getScore() > mStudents[j - 1].getScore())
					swap(mStudents[j], mStudents[j - 1]);
		break;
	}

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
