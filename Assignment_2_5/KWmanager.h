#pragma once

#include <fstream>

#include "ItemList.h"

class KWmanager {

	static const int MAX_ENTRY = 10;

public:
	KWmanager(char *fileName);
	~KWmanager();

	// Basic CRUD operations.
	void insertItem(char *name, int price, int quantity);
	void loadItem();
	void updateItem(int updateIdx, char *newItemName, int newPrice, int newQuantity);
	void deleteItem(int deleteIdx);

	void printItem();
	void saveItem();

	bool checkExistItem(int checkedIdx); // Check wheter the given idx is valid range.

private:
	ItemList mItemList;

	std::fstream mInputFile;
	char mFileName[BUFSIZ];
};