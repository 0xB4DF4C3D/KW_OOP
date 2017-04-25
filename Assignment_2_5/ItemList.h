#pragma once

#include "Item.h"

class ItemList {
public:

	ItemList();
	~ItemList();

	// Basic CRUD operations.
	void insert(const Item& insertItem);
	void update(int targetIdx, const Item& newItem);
	void del(int deleteIdx);
	
	void printAll();	
	void clear();		
	
	Item& at(int idx); // Get item with idx corresonding to given idx.

	int getUsed() const;
private:
	int mCapacity, mUsed;
	Item* mItems;
};

