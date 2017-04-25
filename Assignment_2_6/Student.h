#pragma once
#include "myString.h"

class Student {
public:

	static const size_t NAME_SIZE = 64;
	static const size_t SCORE_MAX = 100;

	enum class Days {
		WED, THU, FRI, NON
	};

	Student();
	~Student();

	// Getters & Setters.
	void setDay(char* day); 
	Days getDay() const; 

	void setName(char* name); 
	const char* getName() const;

	void setScore(int score); 
	int getScore() const;

private:
	Days m_day;
	char m_name[NAME_SIZE];
	int m_score;

};

