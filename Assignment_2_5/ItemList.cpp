#include "ItemList.h"
#include <iostream>

using namespace std;

ItemList::ItemList() {
	mCapacity = 10;
	mUsed = 0;

	mItems = new Item[mCapacity];
}

ItemList::~ItemList() {
	delete[] mItems;
}

void ItemList::insert(const Item& insertItem) {

	// Validate capacity.
	if (mUsed + 1 > mCapacity) {
		cerr << "Maximum number of items is " << mCapacity;
		throw out_of_range("[!] Error. Capacity exceeded.");
	}

	mItems[mUsed++] = insertItem;
}

void ItemList::update(int updateIdx, const Item& newItem) {

	// Validate idx which will be updated.
	if (updateIdx < 1 || updateIdx > mUsed+1) {
		cerr << "updateIdx must be in " << 1 << " ~ " << mUsed + 1 << endl;
		throw invalid_argument("[!] Error. updateIdx is invalid argument.");
	}

	mItems[updateIdx-1] = newItem;
}

void ItemList::del(int deleteIdx) {

	// Validate idx which will be deleted.
	if (deleteIdx < 1 || deleteIdx > mUsed + 1) {
		cerr << "deleteIdx must be in " << 1 << " ~ " << mUsed + 1 << endl;
		throw invalid_argument("[!] Error. deleteIdx is invalid argument.");
	}

	for (int i = deleteIdx-1; i < mUsed - 1; i++)
		mItems[i] = mItems[i + 1];
	mUsed--;
}

void ItemList::printAll() {
	for (int i = 0; i < mUsed; i++) {
		cout << i+1 << ". " << mItems[i].getName() << "($" << mItems[i].getPrice() << ", "
			<< mItems[i].getQuantity() << ")" << endl;
	}
}

void ItemList::clear() {
	mUsed = 0;
}

Item& ItemList::at(int idx) {

	// Validate idx which will be returned.
	if (idx < 1 || idx > mUsed + 1) {
		cerr << "idx must be in " << 1 << " ~ " << mUsed + 1 << endl;
		throw invalid_argument("[!] Error. idx is invalid argument.");
	}

	return mItems[idx-1];
}

int ItemList::getUsed() const {
	return mUsed;
}
