#include "ItemList.h"

#include <iostream>

using namespace std;

ItemList::ItemList() {
}


ItemList::~ItemList() {

	// Traverse all followers
	// and release each from memory.
	Follower* currentFollower = mItem.getHead(), *deletedFollower;

	while (currentFollower != nullptr) {
		deletedFollower = currentFollower;
		currentFollower = currentFollower->getNext();
		delete deletedFollower;
	}

	// Since the Item itself is a member variable of the class, it is automatically destroyed when the class is destroyed.
}

Follower* ItemList::find(const char* word) {

	// Traverse all followers and
	// return a Follower with a name that matches the word.
	Follower* currentFollower = mItem.getHead();

	while (currentFollower != nullptr) {

		if (strcmp(word, currentFollower->getWord()) == 0)
			return currentFollower;

		currentFollower = currentFollower->getNext();
	}

	// If not found till end. return nullptr.
	return nullptr;
}

bool ItemList::isExist(const char* word) {

	// Checks whether there is a follower with the name corresponding to word in current itemList and
	// returns true / false.
	if (find(word) != nullptr)
		return true;
	else
		return false;

}

void ItemList::insert(int idx, Follower* newFollower) {

	Follower* currentFollower = mItem.getHead();

	// If there is no Follower yet.
	if (currentFollower == nullptr) {

		// Set a new Follower to head and exit.
		mItem.setHead(newFollower);
		return;
	}

	// Approach to follower corresponding to idx. 
	// If idx is greater than the total number, the last is accessed.
	for (int i = 0; i < idx && currentFollower->getNext() != nullptr; i++) {
		currentFollower = currentFollower->getNext();
	}

	// Insert a new node at that location.
	newFollower->setNext(currentFollower->getNext());
	currentFollower->setNext(newFollower);
}

int ItemList::size() {

	// Returns the number of followers contained in the current itemList.
	Follower* currentFollower = mItem.getHead();

	int size;
	for (size = 1; currentFollower->getNext() != nullptr; size++, currentFollower = currentFollower->getNext());
	return size;
}

Follower* ItemList::at(int idx) {

	// Returns a follower corresponding to the given idx.
	Follower* theFollower = mItem.getHead();

	for (int i = 0; i < idx; i++) {
		theFollower = theFollower->getNext();

		// If there is no follower corresponding to idx, return nullptr.
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

