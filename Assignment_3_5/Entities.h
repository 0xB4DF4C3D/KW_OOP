#pragma once

#include <list>
#include <memory>

class Entity {

public:

	Entity() {}
	~Entity() {}

	enum class PROP {
		PEOPLE, HOUSE, NAME, ADDRESS
	};
};

class House; // Forward declaration.

class People : public Entity {
public:

	People() {}
	People(const std::string& name) { mName = name; }
	~People() {}

	House* getHouse() const { return mHouse; }
	std::string getName() const { return mName; }
	void setName(const std::string& name) { mName = name; }
	void setHouse(House* house) { mHouse = house; }

private:
	std::string mName;
	House* mHouse;
};

class House : public Entity {
public:

	House() {}
	~House() {};

	void addPeople(std::shared_ptr<People> people) { mPeopleList.push_back(people); }
	std::string getAddress() const { return mAddress; }
	std::list<std::shared_ptr<People>> getPeopleList() const { return mPeopleList; }
	void setAddress(const std::string& address) { mAddress = address; }

private:
	std::string mAddress;
	std::list<std::shared_ptr<People>> mPeopleList;
};