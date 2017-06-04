#include "AddressInfoManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> tokenize(const string& str, const string& delimiters = " ");

AddressInfoManager::AddressInfoManager(const std::string& fileName) {

	ifstream inputFile(fileName);

	string lineBuffer, name, address;
	vector<string> tokens;

	while (!inputFile.eof()) {

		getline(inputFile, lineBuffer);
		cout << lineBuffer << endl;

		tokens = tokenize(lineBuffer, "/");
		name = tokens[0];
		address = tokens[1];

		People* newPeople = new People(name);
		mHouseMap[address].addPeople(newPeople);
		mHouseMap[address].setAddress(address);
		newPeople->setHouse(&mHouseMap[address]);

		mPeopleMap[name].setHouse(&mHouseMap[address]);
		mPeopleMap[name].setName(name);
	}
	cout << endl;
}


AddressInfoManager::~AddressInfoManager() {
}

void AddressInfoManager::showPeople() const {

	int idx = 1;
	for (const auto& people : mPeopleMap) {
		cout << idx++ << ". " << people.second.getName() << " - " << people.second.getHouse()->getAddress() << endl;
	}
	cout << endl;
}

void AddressInfoManager::showHouse() const {

	int idx = 1;
	for (const auto& house : mHouseMap) {
		cout << idx++ << ". " << house.first << " - ";

		for (const auto& resident : house.second.getPeopleList()) {
			cout << resident->getName() << " / ";
		}
		cout << endl;
	}
	cout << endl;
}

void AddressInfoManager::changeName(std::string oldName, std::string newName) {

	if (mPeopleMap.find(oldName) == mPeopleMap.end()) {
		cerr << "[!] Error. there are no " << oldName << endl;
		throw invalid_argument("oldName is invalid argument");
	}

	mPeopleMap[newName] = mPeopleMap[oldName];
	mPeopleMap.erase(oldName);

	mPeopleMap[newName].setName(newName);

	for (const auto& people : mPeopleMap[newName].getHouse()->getPeopleList()) {
		if (people->getName() == oldName) {
			people->setName(newName);
			break;
		}
	}
}

void AddressInfoManager::changeAddress(std::string oldAddress, std::string newAddress) {

	if (mHouseMap.find(oldAddress) == mHouseMap.end()) {
		cerr << "[!] Error. there are no " << oldAddress << endl;
		throw invalid_argument("oldAddress is invalid argument");
	}

	mHouseMap[newAddress] = mHouseMap[oldAddress];
	mHouseMap[newAddress].setAddress(newAddress);

	for (const auto& people : mHouseMap[oldAddress].getPeopleList()) {
		people->setHouse(&mHouseMap[newAddress]);
		mPeopleMap[people->getName()].setHouse(&mHouseMap[newAddress]);
	}

	mHouseMap.erase(oldAddress);
}

vector<string> tokenize(const string& str, const string & delimiters) {

	vector<string> tokens;

	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {

		tokens.push_back(str.substr(lastPos, pos - lastPos));

		lastPos = str.find_first_not_of(delimiters, pos);

		pos = str.find_first_of(delimiters, lastPos);
	}

	return tokens;
}
