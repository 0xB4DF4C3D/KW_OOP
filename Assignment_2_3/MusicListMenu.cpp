#include "MusicListMenu.h"
#include "myString.h"

#include <iostream>

using namespace std;

// Create a MusicListManipulator object with the given file name.
MusicListMenu::MusicListMenu(char* fileName) :mManipulator(fileName) {
}

MusicListMenu::~MusicListMenu() {
}

// List possible options.
void MusicListMenu::printChoice() {
	for (int idx = 0; idx < NUMBER_OF_MENU; idx++)
		cout << idx + 1 << ". " << mMenus[idx] << "    ";
	cout << endl;
}

// Receive the menu number.
int MusicListMenu::input() {
	int menuNumber;

	do {	// Repeat until the correct value is entered in Number.
		cout << "> Input Number : ";
	} while (safeNumInput(cin, menuNumber, 1, NUMBER_OF_MENU));
	cout << endl;

	try {
		switch (menuNumber) {

		case INSERT:
			menu_insert();
			break;

		case UPDATE:
			menu_update();
			break;

		case DELETE:
			menu_delete();
			break;

		case SORT:
			menu_sort();
			break;

		case QUIT:
			return 0;
			break;

		default:
			throw logic_error("[!] Error. in MusicListMenu::input() There is no corresponding case in the switch statement.");
		}
	} catch (const exception& e) {
		cout << e.what() << endl << endl;
	}

	return menuNumber;
}

// If the user selects the INSERT menu.
void MusicListMenu::menu_insert() {
	cout << "** Insert **" << endl;

	unsigned int rank, releaseYear;
	char title[Music::TITLE_SIZE], singer[Music::SINGER_SIZE];

	do { // Repeat until the correct value is entered in Rank.
		cout << "> Rank : ";
	} while (safeNumInput(cin, rank, 0, Music::RANK_MAX));

	do { // Repeat until the correct value is entered in Title.
		cout << "> Title : ";
	} while (safeCstrInput(cin, title, 1, Music::TITLE_SIZE));

	do { // Repeat until the correct value is entered in Singer.
		cout << "> Singer : ";
	} while (safeCstrInput(cin, singer, 1, Music::SINGER_SIZE));

	do { // Repeat until the correct value is entered in ReleaseYear.
		cout << "> ReleaseYear : ";
	} while (safeNumInput(cin, releaseYear, 0, Music::YEAR_MAX));

	mManipulator.insertMusic(rank, title, singer, releaseYear);
}


void MusicListMenu::menu_update() {
	cout << "** Update **" << endl;

	unsigned int oldRank, newRank, releaseYear;
	char title[Music::TITLE_SIZE], singer[Music::SINGER_SIZE];
	
	while (true) {
		do { // Repeat until the correct value is entered in old Rank.
			cout << "> Input rank : ";
		} while (safeNumInput(cin, oldRank, 0, Music::RANK_MAX));

		// In addition, check that the rank exists.
		if (!mManipulator.checkExistMusic(oldRank)) {
			cerr << "[!] Error. there are no " << oldRank << " rank" << endl;
			continue;
		}
		break;
	}

	while (true) {
		do {  // Repeat until the correct value is entered in new Rank.
			cout << "> Rank : ";
		} while (safeNumInput(cin, newRank, 0, Music::RANK_MAX));

		// In addition, make sure that the rank does not already exist.
		if (mManipulator.checkExistMusic(newRank)) {
			cerr << "[!] Error. there are already " << newRank << " rank" << endl;
			continue;
		}
		break;
	}

	do {  // Repeat until the correct value is entered in new Title.
		cout << "> Title : ";
	} while (safeCstrInput(cin, title, 1, Music::TITLE_SIZE));

	do {  // Repeat until the correct value is entered in new Singer.
		cout << "> Singer : ";
	} while (safeCstrInput(cin, singer, 1, Music::SINGER_SIZE));

	do {  // Repeat until the correct value is entered in new ReleaseYear.
		cout << "> ReleaseYear : ";
	} while (safeNumInput(cin, releaseYear, 0, Music::YEAR_MAX));

	mManipulator.updateMusic(oldRank, newRank, title, singer, releaseYear);
}


void MusicListMenu::menu_delete() {
	cout << "** Delete **" << endl;

	int rank;

	while (true) {
		do {  // Repeat until the correct value is entered in Rank.
			cout << "> Input rank : ";
		} while (safeNumInput(cin, rank, 0, Music::RANK_MAX));

		// In addition, check that the rank exists.
		if (!mManipulator.checkExistMusic(rank)) {
			cerr << "[!] Error. there are no " << rank << " rank" << endl;
			continue;
		}
		break;
	}

	mManipulator.deleteMusic(rank);
}


void MusicListMenu::menu_sort() {
	cout << "** Sort **" << endl;

	cout << "1. Sort by the rank    "
		<< "2. Sort by the title    "
		<< "3. Sort by the singer    "
		<< "4. Sort by the release year" << endl;

	int sortType;
	do {  // Repeat until the correct value is entered in sortType.
		cout << "> Input number : ";
	} while (safeNumInput(cin, sortType, 1, 4));

	mManipulator.sortMusic(static_cast<Music::PROP>(sortType));
}