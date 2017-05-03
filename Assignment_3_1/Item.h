#pragma once

#include "Follower.h"

class Item {
public:
	Item();
	~Item();

	char* getWord() const;
	void setWord(const char* word);

	int getSize() const;
	void setSize(int size);

	Follower* getHead() const;
	void setHead(Follower* head);

private:
	char* mWord;
	int mSize;
	Follower* mHead;

};

