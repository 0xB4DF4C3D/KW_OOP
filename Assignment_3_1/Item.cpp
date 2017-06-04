#include "Item.h"

#include <cstring>

Item::Item() {
	mSize = 0;

	// Initialize with nullptr to reduce the number of branches when deleting a Node.
	mHead = nullptr;
	mWord = nullptr;
}


Item::~Item() {
	delete[] mWord;
}

char* Item::getWord() const {
	return mWord;
}

void Item::setWord(const char* word) {
	int wordLength = strlen(word);
	delete[] mWord; // This statement is always safe.
	mWord = new char[wordLength + 1];
	strcpy(mWord, word);
}

int Item::getSize() const {
	return mSize;
}

void Item::setSize(int size) {
	mSize = size;
}

Follower* Item::getHead() const {
	return mHead;
}

void Item::setHead(Follower* head) {
	mHead = head;
}
