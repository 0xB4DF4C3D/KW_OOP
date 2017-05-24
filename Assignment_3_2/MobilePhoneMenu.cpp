#include "MobilePhoneMenu.h"

#include <iostream>

#include "string_jdh.h"

using namespace std;

const char* MobilePhoneMenu::mMenuTitles[] = {
	"Insert product at begginning",
	"Insert product at last",
	"Insert product at position",
	"Delete product",
	"Update product",
	"Search product",
	"Sort by price in ascending order",
	"Display product list",
	"Reverse product list",
	"Exit"
};

MobilePhoneMenu::MobilePhoneMenu() {

}


MobilePhoneMenu::~MobilePhoneMenu() {
}

void MobilePhoneMenu::printChoice() {
	for (int idx = 0; idx < MENU_MAX - 1; idx++)
		cout << idx + 1 << ". " << mMenuTitles[idx] << endl;
	cout << endl;
}

int MobilePhoneMenu::input() {
	int menuNumber;

	do {	// Repeat until the correct value is entered in Number.
		cout << "> Input Number : ";
	} while (safeNumInput(cin, menuNumber, 1, MENU_MAX - 1));
	cout << endl;

	try {
		switch (menuNumber) {
		case MobilePhoneMenu::INSERT_BEGIN:
			menu_insert(emPosition::BEGIN);
			break;
		case MobilePhoneMenu::INSERT_LAST:
			menu_insert(emPosition::LAST);
			break;
		case MobilePhoneMenu::INSERT_POS:
			menu_insert(emPosition::POS);
			break;
		case MobilePhoneMenu::DELETE:
			menu_delete();
			break;
		case MobilePhoneMenu::UPDATE:
			menu_update();
			break;
		case MobilePhoneMenu::SEARCH:
			menu_search();
			break;
		case MobilePhoneMenu::SORT_PRICE:
			menu_sort(MobilePhoneEntry::PROP::PRICE);
			break;
		case MobilePhoneMenu::DISPLAY:
			menu_display();
			break;
		case MobilePhoneMenu::REVERSE:
			menu_reverse();
			break;
		case MobilePhoneMenu::EXIT:
			return 0;
			break;
		default:
			throw logic_error("[!] Error. in MobilePhoneMenu::input() There is no corresponding case in the switch statement.");
		}
	} catch (const exception& e) {
		cout << e.what() << endl << endl;
	}

	return menuNumber;
}

void MobilePhoneMenu::menu_insert(emPosition pos) {

	int idx;

	switch (pos) {
	case MobilePhoneMenu::emPosition::BEGIN:
		cout << "<Insert product at begin>" << endl;
		idx = 0;
		break;
	case MobilePhoneMenu::emPosition::LAST:
		cout << "<Insert product at last>" << endl;
		idx = mMobilePhoneManager.getSize();
		break;
	case MobilePhoneMenu::emPosition::POS:
		cout << "<Insert product at position>" << endl;

		do { // Repeat until the correct value is entered in idx.
			cout << "-> Enter the position of product inserted : ";
		} while (safeNumInput(cin, idx, 0, mMobilePhoneManager.getSize()));
		break;
	}

	char name[MobilePhoneEntry::NAME_SIZE], brand[MobilePhoneEntry::BRAND_SIZE];
	int price;

	do { // Repeat until the correct value is entered in name.
		cout << "-> Enter the product name : ";
	} while (safeCstrInput(cin, name, 1, MobilePhoneEntry::NAME_SIZE));

	do { // Repeat until the correct value is entered in brand.
		cout << "-> Enter the product brand : ";
	} while (safeCstrInput(cin, brand, 1, MobilePhoneEntry::BRAND_SIZE));

	do { // Repeat until the correct value is entered in price.
		cout << "-> Enter the product price : ";
	} while (safeNumInput(cin, price, 0, MobilePhoneEntry::PRICE_MAX));

	mMobilePhoneManager.insertEntry(name, brand, price, idx);

	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;
}

void MobilePhoneMenu::menu_delete() {
	cout << "<Delete product>" << endl;

	char name[MobilePhoneEntry::NAME_SIZE];
	int deletedIdx;

	do {
		do { // Repeat until the correct value is entered in name.
			cout << "-> Enter the product name you want to delete : ";
		} while (safeCstrInput(cin, name, 1, MobilePhoneEntry::NAME_SIZE));
		deletedIdx = mMobilePhoneManager.searchEntry(name);
		if (deletedIdx == -1)
			cout << "There are no " << name << endl;
	} while (deletedIdx == -1);

	mMobilePhoneManager.deleteEntry(deletedIdx);
	cout << "** " << name << " has been deleted from position " << deletedIdx << " **" << endl;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;
}

void MobilePhoneMenu::menu_update() {
	cout << "<Update product>" << endl;

	char oldName[MobilePhoneEntry::NAME_SIZE];
	int updatedIdx;
	do {
		do { // Repeat until the correct value is entered in name.
			cout << "-> Enter the product name : ";
		} while (safeCstrInput(cin, oldName, 1, MobilePhoneEntry::NAME_SIZE));
		updatedIdx = mMobilePhoneManager.searchEntry(oldName);
		if (updatedIdx == -1)
			cout << "There are no " << oldName << endl;
	} while (updatedIdx == -1);

	char name[MobilePhoneEntry::NAME_SIZE], brand[MobilePhoneEntry::BRAND_SIZE];
	int price;

	do { // Repeat until the correct value is entered in name.
		cout << "-> Enter the new product name : ";
	} while (safeCstrInput(cin, name, 1, MobilePhoneEntry::NAME_SIZE));

	do { // Repeat until the correct value is entered in brand.
		cout << "-> Enter the new product brand : ";
	} while (safeCstrInput(cin, brand, 1, MobilePhoneEntry::BRAND_SIZE));

	do { // Repeat until the correct value is entered in price.
		cout << "-> Enter the new product price : ";
	} while (safeNumInput(cin, price, 0, MobilePhoneEntry::PRICE_MAX));


	mMobilePhoneManager.updateEntry(updatedIdx, name, brand, price);

	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;
}

void MobilePhoneMenu::menu_search() {
	cout << "<Search product>" << endl;

	char name[MobilePhoneEntry::NAME_SIZE];

	do { // Repeat until the correct value is entered in name.
		cout << "-> Enter the product name : ";
	} while (safeCstrInput(cin, name, 1, MobilePhoneEntry::NAME_SIZE));

	int searchedIdx;

	searchedIdx = mMobilePhoneManager.searchEntry(name);

	if (searchedIdx == -1)
		cout << "There are no " << name << endl;
	else {
		MobilePhoneEntry* searchedMobilePhoneEntry = mMobilePhoneManager.at(searchedIdx);
		cout << "* At position " << searchedIdx << " *" << endl;
		cout << "Product name  : " << searchedMobilePhoneEntry->getName() << endl;
		cout << "Product brand : " << searchedMobilePhoneEntry->getBrand() << endl;
		cout << "Product price : " << searchedMobilePhoneEntry->getPrice() << endl;
	}

	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;
}

void MobilePhoneMenu::menu_sort(MobilePhoneEntry::PROP sortKey) {
	mMobilePhoneManager.sort(sortKey);
}

void MobilePhoneMenu::menu_display() {

	int size = mMobilePhoneManager.getSize();
	MobilePhoneEntry* currentEntry;

	cout << "<Display product list>" << endl;

	for (int i = 0; i < size; i++) {
		currentEntry = mMobilePhoneManager.at(i);

		cout << "Product name  : " << currentEntry->getName() << endl;
		cout << "Product brand : " << currentEntry->getBrand() << endl;
		cout << "Product price : " << currentEntry->getPrice() << endl << endl;
	}

	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;
}

void MobilePhoneMenu::menu_reverse() {
	cout << "<Reverse product list>" << endl;
	
	mMobilePhoneManager.reverseAll();

	cout << "**The product list has been reversed**" << endl;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;
}
