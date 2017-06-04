#pragma once

#include <list>

class Entity {

public:

	Entity() {}
	~Entity() {}

	enum class PROP {
		PEOPLE, HOUSE, NAME, ADDRESS
	};
};

class House;

class People : public Entity {
public:

	static const size_t NAME_SIZE = BUFSIZ;

	People() {}
	People(const std::string& name) { mName = name; }
	~People() {}

	House* getHouse() const { return mHouse; }
	void setHouse(House* house) { mHouse = house; }
	std::string getName() const { return mName; }
	void setName(const std::string& name) { mName = name; }

private:
	std::string mName;
	House* mHouse;
};

class House : public Entity {
public:

	static const size_t ADDRESS_SIZE = BUFSIZ;

	House() {}
	~House() {};

	void addPeople(People* people) { mPeopleList.push_back(people); }
	std::list<People*> getPeopleList() const { return mPeopleList; }
	std::string getAddress() const { return mAddress; }
	void setAddress(const std::string& address) { mAddress = address; }

private:
	std::string mAddress;
	std::list<People*> mPeopleList;
};