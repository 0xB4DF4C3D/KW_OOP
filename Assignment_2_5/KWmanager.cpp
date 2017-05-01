#include "KWmanager.h"

#include <iostream>
#include <functional>

#include "myString.h"

using namespace std;

// Open the file safely.
void validFileOpen(fstream& stream, const char* fileName, int mode = 3) {
	stream.open(fileName, mode);

	// If it fails to open ...
	if (stream.fail()) {
		cerr << "Failed to open " << fileName << '.' << endl;
		cerr << "Program will be aborted." << endl;
		exit(EXIT_FAILURE);
	};
}


KWmanager::KWmanager(char *fileName) {
	my_cpy(mFileName, fileName); // Save fileName so that load data later.
}

KWmanager::~KWmanager() {
}


void KWmanager::loadItem() {
	validFileOpen(mInputFile, mFileName);

	char *token;
	char lineBuf[BUFSIZ];

	mUsed = 0; // Clear item list by set mUsed 0

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

			mItems[mUsed++] = newItem;
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

	// Validate capacity.
	if (mUsed + 1 > MAX_ENTRY) {
		cerr << "Maximum number of items is " << MAX_ENTRY;
		throw out_of_range("[!] Error. Capacity exceeded.");
	}

	mItems[mUsed++] = Item(name, price, quantity);
	cout << endl;
}

void KWmanager::updateItem(int updateIdx, char *newItemName, int newPrice, int newQuantity) {

	// Validate idx which will be updated.
	if (updateIdx < 1 || updateIdx > mUsed + 1) {
		cerr << "updateIdx must be in " << 1 << " ~ " << mUsed + 1 << endl;
		throw invalid_argument("[!] Error. updateIdx is invalid argument.");
	}

	mItems[updateIdx - 1] = Item(newItemName, newPrice, newQuantity);
	cout << endl;
}

void KWmanager::deleteItem(int deleteIdx) {

	// Validate idx which will be deleted.
	if (deleteIdx < 1 || deleteIdx > mUsed + 1) {
		cerr << "deleteIdx must be in " << 1 << " ~ " << mUsed + 1 << endl;
		throw invalid_argument("[!] Error. deleteIdx is invalid argument.");
	}

	for (int i = deleteIdx - 1; i < mUsed - 1; i++)
		mItems[i] = mItems[i + 1];
	mUsed--;
	cout << endl;
}

void KWmanager::printItem(Item::PROP sortType) {

	// Dynamically allocate a temporary object array for output to preserve the original array.
	Item* tempToPrint = new Item[mUsed];

	// The original index to remember when the array is not sequential.
	int* originSequence = new int[mUsed];
	int tempToSwap;

	// Then copy the values.
	for (int i = 0; i < mUsed; i++) {
		tempToPrint[i].setName(const_cast<char*>(mItems[i].getName()));
		tempToPrint[i].setPrice(mItems[i].getPrice());
		tempToPrint[i].setQuantity(mItems[i].getQuantity());
		originSequence[i] = i+1; // Set the origin sequence.
	}

	// If the sort type is not array order
	if (sortType != Item::PROP::SEQUENCE) {

		// Function wrapper are used to correspond to various sort keys.
		function<bool(int)> sortCustom;

		// Since the keys actually differ in how they compare, 
		// this part (such as a string or number) must be defined before sorting.

		// Here I have simplified code by using an anonymous function called lambda, one of the features of C++ 11.
		switch (sortType) {
		case Item::PROP::NAME:
			sortCustom = [&](int j) {return my_cmp(tempToPrint[j].getName(), tempToPrint[j - 1].getName()) < 0; };
			break;
		case Item::PROP::PRICE:
			sortCustom = [&](int j) {return tempToPrint[j].getPrice() < tempToPrint[j - 1].getPrice(); };
			break;
		case Item::PROP::QUANTITY:
			sortCustom = [&](int j) {return tempToPrint[j].getQuantity() > tempToPrint[j - 1].getQuantity(); };
			break;
		}

		// sort with the custom sort method specified above.
		for (int i = 0; i < mUsed - 1; i++)
			for (int j = mUsed - 1; j > i; j--)
				if (sortCustom(j)) {
					swap(tempToPrint[j], tempToPrint[j - 1]);

					// Swap sequence too!
					tempToSwap = originSequence[j];
					originSequence[j] = originSequence[j - 1];
					originSequence[j - 1] = tempToSwap;
				}
	}

	for (int i = 0; i < mUsed; i++) {
		cout << originSequence[i] << ". " << tempToPrint[i].getName() << "($" << tempToPrint[i].getPrice() << ", "
			<< tempToPrint[i].getQuantity() << ")" << endl;
	}

	delete[] tempToPrint;
	delete[] originSequence;
	
	cout << endl;
}

void KWmanager::saveItem() {
	mInputFile.open(mFileName, ios::out | ios::trunc);

	int idx;
	for (idx = 0; idx < mUsed-1; idx++)			// Convert data to approptiate structure via getInfo method.
		mInputFile << mItems[idx].getInfo() << endl;
	mInputFile << mItems[idx].getInfo();				// Avoid last empty line

	mInputFile.close();
}

bool KWmanager::checkExistItem(int checkedIdx) {
	// Check wheter the given idx is valid range.
	if (checkedIdx < 1 || checkedIdx > mUsed)
		return false;
	else
		return true;
}
