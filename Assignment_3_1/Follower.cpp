#include "Follower.h"

#include <cstring>


Follower::Follower() {
	mWord = nullptr;
	mCount = 1;
	mNext = nullptr;
}

Follower::~Follower() {
	delete[] mWord;
}

char* Follower::getWord() const {
	return mWord;
}

void Follower::setWord(const char* word) {
	int wordLength = strlen(word);
	delete[] mWord;
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
