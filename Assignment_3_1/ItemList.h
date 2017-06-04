#pragma once

#include "Item.h"
#include "Follower.h"


class ItemList {
public:
	ItemList();
	~ItemList();

	void insert(int idx, Follower* newFollower);
	int size();
	Follower* at(int idx);

	char* getWord() const;
	void setWord(const char* word);

	int getSize() const;
	void setSize(int size);

	bool isExist(const char* word); // Check whether there is a follower corresponding to the word in the current List.
	Follower* find(const char* word); // Finds a follower with the name corresponding to word in the current List and returns it.

private:
	Item mItem;
};

