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

	bool isExist(const char* word);
	Follower* find(const char* word);
private:
	Item mItem;
};

