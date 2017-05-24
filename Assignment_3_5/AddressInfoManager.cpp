#include "AddressInfoManager.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

AddressInfoManager::AddressInfoManager(const char* fileName) {

	ifstream inputFile(fileName);
	const int LINE_MAX = BUFSIZ * 2;
	char lineBuffer[LINE_MAX];
	char *token, *context;


	while (!inputFile.eof()) {

		inputFile.getline(lineBuffer, LINE_MAX);
		cout << lineBuffer << endl;

		token = strtok_s(lineBuffer, "/", &context);

	}
	cout << endl;
}


AddressInfoManager::~AddressInfoManager() {
}
