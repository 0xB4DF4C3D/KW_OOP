#include "MobilePhoneManager.h"

#include <functional>
#include <iostream>
#include <string>

using namespace std;

MobilePhoneManager::MobilePhoneManager() {
	mHead = nullptr;
	mTail = nullptr;
	mSize = 0;
}

MobilePhoneManager::~MobilePhoneManager() {

	// Destroy the linked list when the Manager is destroyed.
	MobilePhoneEntry* currentMobilePhoneEntry = mHead, *deletedMobilePhoneEntry;
	while (currentMobilePhoneEntry->mNext != nullptr) {
		deletedMobilePhoneEntry = currentMobilePhoneEntry;
		currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;
		delete deletedMobilePhoneEntry;
		deletedMobilePhoneEntry->mNext = nullptr;
	}
}

void MobilePhoneManager::insertEntry(char name[], char brand[], int price, int idx) {

	if (idx < 0 || idx > mSize) {
		throw invalid_argument("[!] Error. index is invalid argument.");
	}

	MobilePhoneEntry* newMobilePhoneEntry = new MobilePhoneEntry(name, brand, price);

	if (mHead == nullptr) { // If this is the first insert

		// Set Head and Tail to the newly created node.
		mHead = newMobilePhoneEntry;
		mTail = newMobilePhoneEntry;
		newMobilePhoneEntry->mNext = mTail;
		newMobilePhoneEntry->mPrev = mHead;
	} else {

		// Find the node up to idx.
		MobilePhoneEntry* currentMobilePhoneEntry = mHead;
		for (int i = 0; i < idx; i++)
			currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;

		// Insert it in the middle and
		// reestablish the connection relation between neighboring nodes.
		newMobilePhoneEntry->mNext = currentMobilePhoneEntry;
		newMobilePhoneEntry->mPrev = currentMobilePhoneEntry->mPrev;
		currentMobilePhoneEntry->mPrev->mNext = newMobilePhoneEntry;
		currentMobilePhoneEntry->mPrev = newMobilePhoneEntry;
		// The above code block is dependent on the processing order.

		// If the newly added location is a head or tail, 
		// re establish the head and tail.
		if (idx == 0) {
			mHead = newMobilePhoneEntry;
			mTail->mNext = newMobilePhoneEntry;
		} else if (idx == mSize) {
			mTail = newMobilePhoneEntry;
			mHead->mPrev = newMobilePhoneEntry;
		}
	}

	mSize++; // If it is added well, increase Size by 1.
}

int MobilePhoneManager::searchEntry(char name[]) {
	if (mHead == nullptr)
		return -1;

	// Traverse all the nodes starting from mHead and till mHead again.
	MobilePhoneEntry* currentMobilePhoneEntry = mHead;
	
	int idx = 0;
	do {

		// Returns the idx of the node whose name matches the given name during traversal.
		if (strcmp(currentMobilePhoneEntry->getName(), name) == 0)
			return idx;

		currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;
		idx++;
	} while (currentMobilePhoneEntry != mHead);

	return -1; // If it is not found, it returns -1.
}

void MobilePhoneManager::updateEntry(int idx, char newName[], char brand[], int price) {
	MobilePhoneEntry* updatedMobilePhoneEntry = at(idx);

	if (updatedMobilePhoneEntry == nullptr) {
		throw logic_error("[!] Error. There is no updatedMobilePhoneEntry!");
	}

	updatedMobilePhoneEntry->setName(newName);
	updatedMobilePhoneEntry->setBrand(brand);
	updatedMobilePhoneEntry->setPrice(price);
}

void MobilePhoneManager::deleteEntry(int idx) {
	MobilePhoneEntry* deletedMobilePhoneEntry = at(idx);
	
	if (deletedMobilePhoneEntry == nullptr) {
		throw logic_error("[!] Error. There is no deletedMobilePhoneEntry!");
	}

	// If the deleted position is Head or Tail, re establish Head and Tail.
	if (deletedMobilePhoneEntry == mHead) {
		mHead = deletedMobilePhoneEntry->mNext;
		mTail->mNext = mHead;
	} else if (deletedMobilePhoneEntry == mTail) {
		mTail = deletedMobilePhoneEntry->mPrev;
		mHead->mPrev = mTail;
	}

	// Reset the connection relationship of the front and back nodes.
	deletedMobilePhoneEntry->mNext->mPrev = deletedMobilePhoneEntry->mPrev;
	deletedMobilePhoneEntry->mPrev->mNext = deletedMobilePhoneEntry->mNext;

	delete deletedMobilePhoneEntry;
	deletedMobilePhoneEntry = nullptr; // Avoid dangling pointer.

	mSize--; // If successfully erased, reduce size by one.
}

void MobilePhoneManager::sort(MobilePhoneEntry::PROP sortKey) {

	// Sort MusicList using bubble sort according to given sertKey.

	// Function wrapper are used to correspond to various sort keys.
	function<bool(MobilePhoneEntry*)> sortCustom;

	// Since the keys actually differ in how they compare, (such as a string or number)
	// this part must be defined before sorting.

	switch (sortKey) {
	case MobilePhoneEntry::PROP::NAME:
		sortCustom = [](MobilePhoneEntry* j) {return strcmp(j->getName(), j->mPrev->getName()) < 0; };
		break;
	case MobilePhoneEntry::PROP::BRAND:
		sortCustom = [](MobilePhoneEntry* j) {return strcmp(j->getBrand(), j->mPrev->getBrand()) < 0; };
		break;
	case MobilePhoneEntry::PROP::PRICE:
		sortCustom = [](MobilePhoneEntry* j) {return j->getPrice() < j->mPrev->getPrice(); };
		break;
	}

	for (int i = 0; i < mSize - 1; i++)
		for (int j = mSize - 1; j > i; j--) {
			if (sortCustom(at(j))) { // If the order of two neighboring nodes is not correct.
				MobilePhoneEntry* cur = at(j);

				// Change the location of the two nodes.
				cur->mPrev->mPrev->mNext = cur;
				cur->mPrev->mNext = cur->mNext;
				cur->mNext = cur->mPrev;

				cur->mNext->mNext->mPrev = cur->mPrev;
				cur->mPrev = cur->mPrev->mPrev;
				cur->mNext->mPrev = cur;

				// If the changed position is Head or Tail, re establish Tail and Head.
				if (cur == mHead) {
					mHead = cur->mNext;
					mTail->mNext = cur->mNext;
				}
				if (cur->mNext == mHead) {
					mHead = cur;
					mTail->mNext = cur;
				}

				mTail = at(mSize - 1);
			}
		}
}

void MobilePhoneManager::displayAll() const {
	cout << "<Display product list>" << endl;

	MobilePhoneEntry* currentMobilePhoneEntry = mHead;
	while (currentMobilePhoneEntry != nullptr) {
		cout << "Product name  : " << currentMobilePhoneEntry->getName() << endl;
		cout << "Product brand : " << currentMobilePhoneEntry->getBrand() << endl;
		cout << "Product price : " << currentMobilePhoneEntry->getPrice() << endl;
		cout << endl;
		currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;
	}
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

void MobilePhoneManager::reverseAll() {

	MobilePhoneEntry* currentMobilePhoneEntry = mHead, *tempMobilePhoneEntry;
	do {
		currentMobilePhoneEntry = swap(currentMobilePhoneEntry->mNext, currentMobilePhoneEntry->mPrev);
	} while (currentMobilePhoneEntry != mHead);

	swap(mHead, mTail);
}

int MobilePhoneManager::getSize() const {
	return mSize;
}

MobilePhoneEntry* MobilePhoneManager::at(int idx) {

	if (idx < 0 || idx >= mSize) {
		throw invalid_argument("[!] Error. index is invalid argument.");
	}

	MobilePhoneEntry* currentMobilePhoneEntry = mHead;
	for (int i = 0; i < idx; i++)
		currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;

	return currentMobilePhoneEntry;
}

MobilePhoneEntry* MobilePhoneManager::swap(MobilePhoneEntry*& a, MobilePhoneEntry*& b) {
	MobilePhoneEntry* tempMobilePhoneEntry;

	tempMobilePhoneEntry = a;
	a = b;
	b = tempMobilePhoneEntry;

	return tempMobilePhoneEntry;
}



MobilePhoneEntry::MobilePhoneEntry(char name[], char brand[], int price) {
	setName(name);
	setBrand(brand);
	setPrice(price);

	mNext = this;
	mPrev = this;
}

const char* MobilePhoneEntry::getName() const {
	return mName;
}

void MobilePhoneEntry::setName(char name[]) {
	int newNameLength = strlen(name);

	if (newNameLength > MobilePhoneEntry::NAME_SIZE) {
		throw invalid_argument("[!] Error. name length is too long!");
	}

	strcpy(mName, name);
}

const char* MobilePhoneEntry::getBrand() const {
	return mBrand;
}

void MobilePhoneEntry::setBrand(char brand[]) {
	int newBrandLength = strlen(brand);

	if (newBrandLength > MobilePhoneEntry::BRAND_SIZE) {
		throw invalid_argument("[!] Error. brand length is too long!");
	}

	strcpy(mBrand, brand);
}

int MobilePhoneEntry::getPrice() const {
	return mPrice;
}

void MobilePhoneEntry::setPrice(int price) {

	if (price > MobilePhoneEntry::PRICE_MAX) {
		throw invalid_argument("[!] Error. price value is too big!");
	}

	mPrice = price;
}


