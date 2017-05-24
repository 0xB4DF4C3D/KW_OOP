#include "KWmenu.h"

#include <iostream>

#include "myString.h"

using namespace std;

// Create a KWmanager object with the given file name.
KWmenu::KWmenu(char *fileName) :mKWmanager(fileName) {
}

KWmenu::~KWmenu() {
}

// List possible options.
void KWmenu::printChoice() {
	for (int idx = 0; idx < NUMBER_OF_MENU; idx++)
		cout << idx + 1 << ". " << mMenus[idx] << "    ";
	cout << endl;
}

// Receive the menu number.
int KWmenu::input() {
	int menuNumber;

	do {	// Repeat until the correct value is entered in Number.
		cout << "> Input Number : ";
	} while (safeNumInput(cin, menuNumber, 1, NUMBER_OF_MENU));
	cout << endl;

	try {
		switch (menuNumber) {

		case LOAD:
			menu_load();
			break;

		case INSERT:
			menu_insert();
			break;

		case UPDATE:
			menu_update();
			break;

		case DELETE:
			menu_delete();
			break;

		case PRINT:
			menu_print();
			break;

		case SAVE:
			menu_save();
			break;

		case QUIT:
			return 0;
			break;

		default:
			throw logic_error("[!] Error. in KWmenu::input() There is no corresponding case in the switch statement.");
		}
	} catch (const exception& e) {
		cout << e.what() << endl << endl;
	}

	return menuNumber;
}

void KWmenu::menu_load() {
	mKWmanager.loadItem();	// Load items using the first given fileName.
}

void KWmenu::menu_insert() {

	cout << "** Insert **" << endl;

	int price, quantity;
	char itemName[Item::NAME_SIZE];

	do {	// Repeat until the correct value is entered in itemName.
		cout << "> Item Name : ";
	} while (safeCstrInput(cin, itemName, 1, Item::NAME_SIZE));

	do {	// Repeat until the correct value is entered in price.
		cout << "> Price : ";
	} while (safeNumInput(cin, price, 0, INT_MAX));

	do {	// Repeat until the correct value is entered in quantity.
		cout << "> Quantity : ";
	} while (safeNumInput(cin, quantity, 0, INT_MAX));

	mKWmanager.insertItem(itemName, price, quantity);
}

void KWmenu::menu_update() {
	cout << "** Update **" << endl;

	int targetIdx, newPrice, newQuantity;
	char newItemName[Item::NAME_SIZE];

	while (true) {
		do {	// Repeat until the correct value is entered in sequence.
			cout << "> Input sequence : ";
		} while (safeNumInput(cin, targetIdx, 1, INT_MAX));
		
		// In addition, check that the sequence exists.
		if (!mKWmanager.checkExistItem(targetIdx)) {
			cerr << "[!] Error. there are no " << targetIdx << " sequence" << endl;
			continue;
		}
		break;
	}

	do {	// Repeat until the correct value is entered in itemName.
		cout << "> Item Name : ";
	} while (safeCstrInput(cin, newItemName, 1, Item::NAME_SIZE));

	do {	// Repeat until the correct value is entered in price.
		cout << "> Price : ";
	} while (safeNumInput(cin, newPrice, 0, INT_MAX));

	do {	// Repeat until the correct value is entered in quantity.
		cout << "> Quantity : ";
	} while (safeNumInput(cin, newQuantity, 0, INT_MAX));

	mKWmanager.updateItem(targetIdx, newItemName, newPrice, newQuantity);
}

void KWmenu::menu_delete() {
	cout << "** Delete **" << endl;

	int deleteIdx;

	while (true) {
		do {	// Repeat until the correct value is entered in sequence.
			cout << "> Input sequence : ";
		} while (safeNumInput(cin, deleteIdx, 1, INT_MAX));

		// In addition, check that the sequence exists.
		if (!mKWmanager.checkExistItem(deleteIdx)) {
			cerr << "[!] Error. there are no " << deleteIdx << " sequence" << endl;
			continue;
		}
		break;
	}

	mKWmanager.deleteItem(deleteIdx);
}

void KWmenu::menu_print() {

	cout << "1. Sequence    "
		<< "2. Name    "
		<< "3. Price    "
		<< "4. Quantity" << endl;

	int sortType;
	do {  // Repeat until the correct value is entered in sortType.
		cout << "> Input number : ";
	} while (safeNumInput(cin, sortType, 1, 4));

	mKWmanager.printItem(static_cast<Item::PROP>(sortType));
}

void KWmenu::menu_save() {
	mKWmanager.saveItem(); // Load items using the first given fileName.
}
