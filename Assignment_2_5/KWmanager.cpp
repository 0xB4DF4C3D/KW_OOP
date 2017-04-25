#include "KWmanager.h"

#include <iostream>

#include "myString.h"

using namespace std;

KWmanager::KWmanager(char *fileName) {
	my_cpy(mFileName, fileName); // Save fileName so that load data later.
}

KWmanager::~KWmanager() {
}


void KWmanager::loadItem() {
	mInputFile.open(mFileName);

	char *token;
	char lineBuf[BUFSIZ];

	mItemList.clear();
	// If the file structure is inappropriate for the following reasons:
	//		If the letter comes where the numbers should come.
	//		The range of values is too small or too large.
	// If so, the program will be aborted.
	try {
		// Each line is searched and the data is read.
		do {
			Item newItem;

			mInputFile.getline(lineBuf, BUFSIZ);

			token = my_tok(lineBuf, "/");
			newItem.setName(token);

			token = my_tok(NULL, "/");
			if (!validateNumeric(token))
				throw exception("[!] Error. Price must be a number.");
			newItem.setPrice(atoi(token));

			token = my_tok(NULL, "/");
			if (!validateNumeric(token))
				throw exception("[!] Error. Quantity must be a number.");
			newItem.setQuantity(atoi(token));

			mItemList.insert(newItem);
		} while (!mInputFile.eof());
	} catch (const exception& e) {
		cerr << e.what() << endl;
		cerr << "Program will be aborted." << endl;
		mInputFile.close();
		exit(EXIT_FAILURE);
	}

	mInputFile.close();
}

void KWmanager::insertItem(char *name, int price, int quantity) {

	mItemList.insert(Item(name, price, quantity));
	cout << endl;
}

void KWmanager::updateItem(int updateIdx, char *newItemName, int newPrice, int newQuantity) {

	mItemList.update(updateIdx, Item(newItemName, newPrice, newQuantity));
	cout << endl;
}

void KWmanager::deleteItem(int deleteIdx) {

	mItemList.del(deleteIdx);
	cout << endl;
}

void KWmanager::printItem() {

	mItemList.printAll();
	cout << endl;
}

void KWmanager::saveItem() {
	mInputFile.open(mFileName, ios::out | ios::trunc);

	int idx;
	for (idx = 1; idx < mItemList.getUsed(); idx++)			// Convert data to approptiate structure via getInfo method.
		mInputFile << mItemList.at(idx).getInfo() << endl;
	mInputFile << mItemList.at(idx).getInfo();				// Avoid last empty line

	mInputFile.close();
}

bool KWmanager::checkExistItem(int checkedIdx) {
	// Check wheter the given idx is valid range.
	if (checkedIdx < 1 || checkedIdx > mItemList.getUsed())
		return false;
	else
		return true;
}
