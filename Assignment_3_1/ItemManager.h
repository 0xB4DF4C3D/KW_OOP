#pragma once

#include "ItemList.h"

class ItemManager {
public:
	ItemManager(const char* fileName);
	~ItemManager();

	// This class only provides functions that show only result values.
	void printResult();

private:
	void makeSet();		// For creating a unique Item list.
	void makeLink();	// For creating links for each ItemList.

	// Returns an itemList with item names corresponding to word from itemList.
	ItemList* find(ItemList* itemList, int itemListSize, const char* word);

	ItemList mAllWords;	// All the words.
	ItemList* mSet;		// All unique words.
	int mSetSize;		// Number of unique words.
};

