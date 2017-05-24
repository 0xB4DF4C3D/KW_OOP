#pragma once

#include "Student.h"

class StudentManager {
public:
	StudentManager(const char* fileName);
	~StudentManager();

	void printOldestStudent();	// Output the information of the oldest student.
	void printAll();			// Print out information for all students.

private:
	Student* mStudentList;
	int mNumberOfStudent;

};