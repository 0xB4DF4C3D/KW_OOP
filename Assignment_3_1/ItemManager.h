#pragma once

#include "ItemList.h"

class ItemManager {
public:
	ItemManager(const char* fileName);
	~ItemManager();

	void printResult();

private:
	void makeSet();
	void makeLink();
	ItemList* find(ItemList* itemList, int itemListSize, const char* word);
	ItemList mAllWords;

	ItemList* mSet;
	int mSetSize;
};

