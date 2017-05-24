#pragma once
#include "Student.h"




class OOP {

	static const size_t MAX_STUDENT = 10;

public:

	enum SortKeys {
		NAME = 1, SCORE
	};

	virtual void PrintTitle(int num) = 0;
	void pushBack(Student newStudent);
	void printAll(SortKeys sortKey);

protected:
	Student mStudents[MAX_STUDENT];
	int mStudentSize = 0;


};

