#include <iostream>

#include "Land.h"
#include "string_jdh.h"

using namespace std;

int main() {

	int inputWidth, inputHeight;
	do {
		cout << "Size of total land X, Y : ";

	} while (safeNumInput(cin, inputWidth, 1, 9999, false) ||
		safeNumInput(cin, inputHeight, 1, 9999, true));  // Repeat until the correct value is entered in width and size.

	Land land1(inputWidth, inputHeight);
	land1.setLandFromConsole();


	Land::Codes occupyResult;
	Land::Status attacker = Land::KOREAN;
	int occupyDate;
	occupyResult = land1.occupuy(attacker, occupyDate);

	switch (occupyResult) {
	case Land::NO_SOLDIER:
		cout << "There are no Korean soldiers." << endl;
		break;
	case Land::SURROUNDED:
		cout << "Because Korean soldiers are surrounded by"
			<< "empty land. they can not occupy the land of"
			<< "Japanese soldiers." << endl;
		break;
	case Land::NO_LAND_TO_OCCUPUY:
		cout << "There is no land to occupy." << endl;
		break;
	case Land::SUCCESS_OCCUPUY:
		cout << "The date when Korean soldiers occupied all the"
			<< "land of Japanese : " << occupyDate << endl;
		break;
	default:
		cerr << " ERROR ";
		break;
	}

	return EXIT_SUCCESS;
}