#pragma once
class Student {
public:

	static const size_t NAME_SIZE = 128, MAIL_SIZE = 128, PHONE_SIZE = 32;
	static const size_t AGE_MAX = 999;

	Student();
	~Student();

	// Getters & Setters.
	void setName(char *inName);
	const char* getName();

	void setMail(char *inMail);
	const char* getMail();

	void setPhone(char *inPhone);
	const char* getPhone();

	void setIdNum(int inIdNum);
	int getIdNum();

	void setAge(int inAge);
	int getAge();

	void setStudent(char *inName, char *inMail, char *inPhone, int inIdNumber, int inAge);
	
	// Output current information.
	void print();

private:
	char *S_name = nullptr;
	char *S_mail = nullptr;
	char *S_phone = nullptr;
	int S_idnum = 0;
	int S_age = 0;

};

