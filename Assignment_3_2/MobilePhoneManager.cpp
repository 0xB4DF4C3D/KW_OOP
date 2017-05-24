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

void MobilePhoneManager::insertEntry(char name[], char brand[], int price, int idx) {

	if (idx < 0 || idx > mSize) {
		throw invalid_argument("error");
	}

	MobilePhoneEntry* newMobilePhoneEntry = new MobilePhoneEntry(name, brand, price);

	if (mHead == nullptr) {
		mHead = newMobilePhoneEntry;
		mTail = newMobilePhoneEntry;
		newMobilePhoneEntry->mNext = mTail;
		newMobilePhoneEntry->mPrev = mHead;
	} else {
		MobilePhoneEntry* currentMobilePhoneEntry = mHead;
		for (int i = 0; i < idx; i++)
			currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;

		newMobilePhoneEntry->mNext = currentMobilePhoneEntry;
		newMobilePhoneEntry->mPrev = currentMobilePhoneEntry->mPrev;
		currentMobilePhoneEntry->mPrev->mNext = newMobilePhoneEntry;
		currentMobilePhoneEntry->mPrev = newMobilePhoneEntry;

		if (idx == 0) {
			mHead = newMobilePhoneEntry;
			mTail->mNext = newMobilePhoneEntry;
		} else if (idx == mSize) {
			mTail = newMobilePhoneEntry;
			mHead->mPrev = newMobilePhoneEntry;
		}
	}

	mSize++;
}

int MobilePhoneManager::searchEntry(char name[]) {
	MobilePhoneEntry* currentMobilePhoneEntry = mHead;
	int idx = 0;

	do {
		if (strcmp(currentMobilePhoneEntry->getName(), name) == 0)
			return idx;
		currentMobilePhoneEntry = currentMobilePhoneEntry->mNext;
		idx++;
	} while (currentMobilePhoneEntry != mHead);

	return -1;
}

void MobilePhoneManager::updateEntry(int idx, char newName[], char brand[], int price) {
	MobilePhoneEntry* updatedMobilePhoneEntry = at(idx);

	if (updatedMobilePhoneEntry == nullptr) {
		throw invalid_argument("error");
	}

	updatedMobilePhoneEntry->setName(newName);
	updatedMobilePhoneEntry->setBrand(brand);
	updatedMobilePhoneEntry->setPrice(price);
}

void MobilePhoneManager::deleteEntry(int idx) {
	MobilePhoneEntry* deletedMobilePhoneEntry = at(idx);
	
	if (deletedMobilePhoneEntry == nullptr) {
		throw invalid_argument("error");
	}

	if (deletedMobilePhoneEntry == mHead) {
		mHead = deletedMobilePhoneEntry->mNext;
		mTail->mNext = mHead;
	} else if (deletedMobilePhoneEntry == mTail) {
		mTail = deletedMobilePhoneEntry->mPrev;
		mHead->mPrev = mTail;
	}

	deletedMobilePhoneEntry->mNext->mPrev = deletedMobilePhoneEntry->mPrev;
	deletedMobilePhoneEntry->mPrev->mNext = deletedMobilePhoneEntry->mNext;
	delete deletedMobilePhoneEntry;
	deletedMobilePhoneEntry = nullptr;

	mSize--;
}

void MobilePhoneManager::sort(MobilePhoneEntry::PROP sortKey) {

	// Sort MusicList using bubble sort according to given sertKey.

	// Function wrapper are used to correspond to various sort keys.
	function<bool(MobilePhoneEntry*)> sortCustom;

	// Since the keys actually differ in how they compare, 
	// this part (such as a string or number) must be defined before sorting.

	switch (sortKey) {
	case MobilePhoneEntry::PROP::NAME:
		sortCustom = [&](MobilePhoneEntry* j) {return strcmp(j->getName(), j->mPrev->getName()) < 0; };
		break;
	case MobilePhoneEntry::PROP::BRAND:
		sortCustom = [&](MobilePhoneEntry* j) {return strcmp(j->getBrand(), j->mPrev->getBrand()) < 0; };
		break;
	case MobilePhoneEntry::PROP::PRICE:
		sortCustom = [&](MobilePhoneEntry* j) {return j->getPrice() < j->mPrev->getPrice(); };
		break;
	}

	for (int i = 0; i < mSize - 1; i++)
		for (int j = mSize - 1; j > i; j--) {
			if (sortCustom(at(j))) {
				MobilePhoneEntry* cur = at(j);

				cur->mPrev->mPrev->mNext = cur;
				cur->mPrev->mNext = cur->mNext;
				cur->mNext = cur->mPrev;

				cur->mNext->mNext->mPrev = cur->mPrev;
				cur->mPrev = cur->mPrev->mPrev;
				cur->mNext->mPrev = cur;

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
	for (int i = 0; i < mSize; i++) {
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

MobilePhoneEntry * MobilePhoneManager::at(int idx) {

	if (idx < 0 || idx >= mSize) {
		throw invalid_argument("error.");
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
		throw invalid_argument("error");
	}

	strcpy(mName, name);
}

const char* MobilePhoneEntry::getBrand() const {
	return mBrand;
}

void MobilePhoneEntry::setBrand(char brand[]) {
	int newBrandLength = strlen(brand);

	if (newBrandLength > MobilePhoneEntry::BRAND_SIZE) {
		throw invalid_argument("error");
	}

	strcpy(mBrand, brand);
}

int MobilePhoneEntry::getPrice() const {
	return mPrice;
}

void MobilePhoneEntry::setPrice(int price) {

	if (price > MobilePhoneEntry::PRICE_MAX) {
		throw invalid_argument("error");
	}

	mPrice = price;
}


