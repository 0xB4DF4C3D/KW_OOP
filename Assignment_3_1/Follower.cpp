#include "Follower.h"

#include <cstring>

Follower::Follower() {
	mCount = 1;

	// Initialize with nullptr to reduce the number of branches when deleting a Node.
	mNext = nullptr;
	mWord = nullptr;
}

Follower::Follower(const char* word) {
	mCount = 1;
	mNext = nullptr;
	mWord = nullptr;
	setWord(word);
}

Follower::~Follower() {
	delete[] mWord;
}

char* Follower::getWord() const {
	return mWord;
}

void Follower::setWord(const char* word) {
	int wordLength = strlen(word);
	delete[] mWord; // This statement is always safe.
	mWord = new char[wordLength + 1];
	strcpy(mWord, word);
}

int Follower::getCount() const {
	return mCount;
}

void Follower::setCount(int count) {
	mCount = count;
}

Follower* Follower::getNext() const {
	return mNext;
}

void Follower::setNext(Follower* next) {
	mNext = next;
}
