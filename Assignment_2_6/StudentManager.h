#pragma once
#include "Days.h"

class StudentManager {
public:
	StudentManager(char *fileName);
	~StudentManager();

	void printItem(Student::Days day, OOP::SortKeys sortKey);
	
private:
	CDays::Wed mWed;
	CDays::Thu mThu;
	CDays::Fri mFri;
	CDays::None mNone;

};

