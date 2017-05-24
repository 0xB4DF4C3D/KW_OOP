#include "Student.h"

#include <iostream>

using namespace std;

Student::Student() {
}


Student::~Student() {
}

void Student::setDay(char* day) {

	// Set the day value via the passed characters.
	if (my_cmp("수", day) == 0) {
		m_day = Student::Days::WED;
	} else if (my_cmp("목", day) == 0) {
		m_day = Student::Days::THU;
	} else if (my_cmp("금", day) == 0) {
		m_day = Student::Days::FRI;
	} else if (my_cmp("미수강", day) == 0) {
		m_day = Student::Days::NON;
	} else {
		cerr << "[!] Errror. There are no " << day << endl;
		throw invalid_argument("invalid argument in Student::setDay");
	}
}

Student::Days Student::getDay() const {
	return m_day;
}

void Student::setName(char* name) {
	if (my_len(name) < 1 || NAME_SIZE < my_len(name)) {
		cerr << "[!] Errror. name length must be in " << 1 << " ~ " << NAME_SIZE << endl;
		throw invalid_argument("invalid argument in Student::setName");
	}
	my_cpy(m_name, name);
}

const char* Student::getName() const {
	return m_name;
}

void Student::setScore(int score) {
	if (score < 0 || SCORE_MAX < score) {
		cerr << "[!] Errror. score must be in " << 0 << " ~ " << SCHAR_MAX << endl;
		throw invalid_argument("invalid argument in Student::setScore");
	}
	m_score = score;
}

int Student::getScore() const {
	return m_score;
}
