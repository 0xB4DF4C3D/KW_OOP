#include "Item.h"
#include "myString.h"
#include <cmath>

using namespace std;

Item::Item() {
}

Item::Item(char *name, int price, int quantity) {
	my_cpy(mName, name);
	mPrice = price;
	mQuantity = quantity;
}

Item::~Item() {
}

const char* Item::getInfo() {
	// Points to the beginning of mInfo.
	char *currentTempPtr = mInfo;

	// I used pointers because it was troublesome to implement strcat.
	// hope for understanding

	// Concatenate name to mInfo.
	char *currentOriginPtr = mName;
	while (*currentOriginPtr != NULL) {
		*currentTempPtr = *currentOriginPtr;

		currentTempPtr++;
		currentOriginPtr++;
	}
	*currentTempPtr = '/';
	currentTempPtr++;

	// Concatenate price to mInfo.
	char buf[256];
	_itoa_s(mPrice, buf, 10);
	currentOriginPtr = buf;
	while (*currentOriginPtr != NULL) {
		*currentTempPtr = *currentOriginPtr;

		currentTempPtr++;
		currentOriginPtr++;
	}
	*currentTempPtr = '/';
	currentTempPtr++;

	// Concatenate quantity to mInfo.
	_itoa_s(mQuantity, buf, 10);
	currentOriginPtr = buf;
	while (*currentOriginPtr != NULL) {
		*currentTempPtr = *currentOriginPtr;
		
		currentTempPtr++;
		currentOriginPtr++;
	}
	*currentTempPtr = '\0';
	return mInfo;
}

const char *Item::getName() {
	return mName;
}

void Item::setName(char *name) {
	my_cpy(mName, name);
}

int Item::getPrice() {
	return mPrice;
}

void Item::setPrice(int price) {
	mPrice = price;
}

int Item::getQuantity() {
	return mQuantity;
}

void Item::setQuantity(int quantity) {
	mQuantity = quantity;
}
