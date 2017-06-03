#pragma once

#include <list>

class House;

class Person {
public:

	static const size_t NAME_SIZE = BUFSIZ;

	Person(House* house) { mHouse = house; };
	~Person() {};
private:
	House* mHouse;
};

class House {
public:

	static const size_t ADDRESS_SIZE = BUFSIZ;

	House(std::string address) { mAddress = address; }
	~House() {};

	std::string getAddress() const { return mAddress; }
	void setAddress(const std::string& address) { mAddress = address; }
	void addPerson(Person* person) { mPersonList.push_back(person); }
	std::list<Person*> getPersonList() const { return mPersonList; }

private:
	std::list<Person*> mPersonList;
	std::string mAddress;
};