#include "Student.h"

#include <iostream>

#include "myString.h"

using namespace std;

Student::Student() {
}

Student::~Student() {
	// Delete allocated memories.
	delete[] S_name;
	delete[] S_mail;
	delete[] S_phone;
}

void Student::setName(char *inName) {
	delete[] S_name; // Delete an existing allocated dynamic string.

	int nameLength = my_len(inName);

	if (nameLength < 1 || NAME_SIZE < nameLength) {
		cerr << "Name length must be in " << 0 << " ~ " << NAME_SIZE << endl;
		throw invalid_argument("[!] Error. Name is invalid argument.");
	}

	S_name = new char[nameLength + 1];	// After assigning a new one,
	my_cpy(S_name, inName);					// copy the new name to it.
}

const char* Student::getName() {
	return S_name;
}

void Student::setMail(char *inMail) {
	delete[] S_mail; // Delete an existing allocated dynamic string.

	int MailLength = my_len(inMail);

	if (MailLength < 1 || MAIL_SIZE < MailLength) {
		cerr << "Mail length must be in " << 0 << " ~ " << MAIL_SIZE << endl;
		throw invalid_argument("[!] Error. Mail is invalid argument.");
	}

	S_mail = new char[my_len(inMail) + 1];	// After assigning a new one,
	my_cpy(S_mail, inMail);					// copy the new mail to it.
}

const char* Student::getMail() {
	return S_mail;
}

void Student::setPhone(char *inPhone) {
	delete[] S_phone; // Delete an existing allocated dynamic string.

	int phoneLength = my_len(inPhone);

	if (phoneLength < 1 || PHONE_SIZE < phoneLength) {
		cerr << "Phone length must be in " << 0 << " ~ " << PHONE_SIZE << endl;
		throw invalid_argument("[!] Error. Phone is invalid argument.");
	}

	S_phone = new char[phoneLength + 1];	// After assigning a new one,
	my_cpy(S_phone, inPhone);					// copy the new phone to it.
}

const char* Student::getPhone() {
	return S_phone;
}

void Student::setIdNum(int inIdNum) {
	S_idnum = inIdNum;
}

int Student::getIdNum() {
	return S_idnum;
}

void Student::setAge(int inAge) {
	if (inAge < 0 || AGE_MAX < inAge) {
		cerr << "Age must be in " << 0 << " ~ " << Student::AGE_MAX << endl;
		throw invalid_argument("[!] Error. Age is invalid argument.");
	}
	S_age = inAge;
}

int Student::getAge() {
	return S_age;
}

void Student::setStudent(char *inName, char *inMail, char *inPhone, int inIdNum, int inAge) {

	setName(inName);
	setMail(inMail);
	setPhone(inPhone);
	setIdNum(inIdNum);
	setAge(inAge);

}

void Student::print() {
	cout << getName() << "      "
		<< getMail() << "      "
		<< getPhone() << "      "
		<< getIdNum() << "      "
		<< getAge() << endl;
}
