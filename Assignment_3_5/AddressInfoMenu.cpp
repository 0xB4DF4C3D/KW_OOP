#include "AddressInfoMenu.h"

#include <iostream>

#include "string_jdh.h"

using namespace std;

const char* AddressInfoMenu::MenuTitle[] = {
	"Show People",
	"Show House",
	"Change Name",
	"Change Address",
	"Quit"
};

AddressInfoMenu::AddressInfoMenu(const char* fileName):mManager(fileName) {

}


AddressInfoMenu::~AddressInfoMenu() {
}

void AddressInfoMenu::printChoice() {
	for (int idx = 0; idx < MENU_MAX - 1; idx++)
		cout << idx + 1 << ". " << MenuTitle[idx] << "    ";
	cout << endl;
}

int AddressInfoMenu::input() {
	int menuNumber;

	do {	// Repeat until the correct value is entered in Number.
		cout << "> Input Number : ";
	} while (safeNumInput(cin, menuNumber, 1, MENU_MAX - 1));
	cout << endl;

	try {
		switch (menuNumber) {
		case AddressInfoMenu::SHOW_PEOPLE:
			break;
		case AddressInfoMenu::SHOW_HOUSE:
			break;
		case AddressInfoMenu::CHANGE_NAME:
			break;
		case AddressInfoMenu::CHANGE_ADDRESS:
			break;
		case AddressInfoMenu::QUIT:
			return 0;
			break;
		default:
			throw logic_error("[!] Error. in AddressInfoMenu::input() There is no corresponding case in the switch statement.");
			break;
		}
	} catch (const exception& e) {
		cout << e.what() << endl << endl;
	}

	return menuNumber;
}

void AddressInfoMenu::menu_show(Entity showedEntity) {
	switch (showedEntity) {
	case AddressInfoMenu::Entity::PERSON:

		break;
	case AddressInfoMenu::Entity::HOUSE:

		break;
	}
}
