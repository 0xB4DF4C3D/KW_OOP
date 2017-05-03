#include "ItemList.h"

#include <iostream>

using namespace std;

ItemList::ItemList() {
}


ItemList::~ItemList() {

	Follower* currentFollower = mItem.getHead(), *deletedFollower;

	while (currentFollower != nullptr) {

		deletedFollower = currentFollower;
		currentFollower = currentFollower->getNext();
		delete deletedFollower;
	}
}

Follower* ItemList::find(const char* word) {

	Follower* currentFollower = mItem.getHead();

	while (currentFollower != nullptr) {

		if (strcmp(word, currentFollower->getWord()) == 0)
			return currentFollower;

		currentFollower = currentFollower->getNext();
	}

	return nullptr;
}

bool ItemList::isExist(const char* word) {

	if (find(word) != nullptr)
		return true;
	else
		return false;

}

void ItemList::insert(int idx, Follower* newFollower) {

	Follower* currentFollower = mItem.getHead(), *nextFollower = nullptr;

	if (currentFollower == nullptr) {
		mItem.setHead(newFollower);
		return;
	}

	for (int i = 0; i < idx && currentFollower->getNext() != nullptr; i++) {
		currentFollower = currentFollower->getNext();
	}
	nextFollower = currentFollower->getNext();
	currentFollower->setNext(newFollower);
	newFollower->setNext(nextFollower);
}

int ItemList::size() {

	Follower* currentFollower = mItem.getHead();
	int size;

	for (size = 1; currentFollower->getNext() != nullptr; size++, currentFollower = currentFollower->getNext());

	return size;
}

Follower* ItemList::at(int idx) {

	Follower* theFollower = mItem.getHead();

	for (int i = 0; i < idx; i++) {

		theFollower = theFollower->getNext();

		if (theFollower == nullptr)
			return nullptr;
	}

	return theFollower;
}

char * ItemList::getWord() const {
	return mItem.getWord();
}

void ItemList::setWord(const char* word) {
	mItem.setWord(word);
}

int ItemList::getSize() const {
	return mItem.getSize();
}

void ItemList::setSize(int size) {
	mItem.setSize(size);
}

