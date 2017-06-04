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

AddressInfoMenu::AddressInfoMenu(const std::string& fileName) :mManager(fileName) {

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
		case SHOW_PEOPLE:
			menu_show(Entity::PROP::PEOPLE);
			break;
		case SHOW_HOUSE:
			menu_show(Entity::PROP::HOUSE);
			break;
		case CHANGE_NAME:
			menu_change(Entity::PROP::NAME);
			break;
		case CHANGE_ADDRESS:
			menu_change(Entity::PROP::ADDRESS);
			break;
		case QUIT:
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

void AddressInfoMenu::menu_show(Entity::PROP showedEntity) {
	switch (showedEntity) {
	case Entity::PROP::PEOPLE:
		mManager.showPeople();
		break;
	case Entity::PROP::HOUSE:
		mManager.showHouse();
		break;
	default:
		throw logic_error("[!] Error. in menu_show::input() There is no corresponding case in the switch statement.");
		break;
	}
}

void AddressInfoMenu::menu_change(Entity::PROP changedEntity) {

	string oldProperty, newProperty;

	cout << "From: ";
	getline(cin, oldProperty);
	cout << "To: ";
	getline(cin, newProperty);

	switch (changedEntity) {
	case Entity::PROP::NAME:
		mManager.changeName(oldProperty, newProperty);
		break;
	case Entity::PROP::ADDRESS:
		mManager.changeAddress(oldProperty, newProperty);
		break;
	default:
		throw logic_error("[!] Error. in menu_change::input() There is no corresponding case in the switch statement.");
		break;
	}
}
