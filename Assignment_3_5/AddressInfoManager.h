#pragma once

#include <map>
#include <list>
#include <string>

#include "Entities.h"

class AddressInfoManager {
public:

	AddressInfoManager(const std::string& fileName);
	~AddressInfoManager();

	void showPeople() const;
	void showHouse() const;
	void changeName(std::string oldName, std::string newName);
	void changeAddress(std::string oldAddress, std::string newAddress);

private:
	std::map<std::string, House> mHouseMap;
	std::map<std::string, People> mPeopleMap;

};

