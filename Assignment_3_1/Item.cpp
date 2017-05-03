#include "Item.h"

#include <cstring>


Item::Item() {
	mWord = nullptr;
	mSize = 0;
	mHead = nullptr;
}


Item::~Item() {
	delete[] mWord;
}

char* Item::getWord() const {
	return mWord;
}

void Item::setWord(const char* word) {
	int wordLength = strlen(word);
	delete[] mWord;
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
