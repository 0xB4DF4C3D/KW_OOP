#pragma once

#include "Node.h"

class ItemNode : public Node {
private:
	char	mName[64];
	int		mCount;
	int		mPrice;

public:
	ItemNode(const char name[], int count, int price) {
		strcpy(mName, name);
		mCount = count;
		mPrice = price;
	}

	void addCount(int amount) { mCount += amount; }
	bool subCount(int amount) { if (amount > mCount) return false; else mCount -= amount; return true; }

	// Return category to which item belongs.
	Node* getCategory() {
		Node* myCategory = this;
		while (myCategory->getUp() != NULL)
			myCategory = myCategory->getUp();
		return myCategory;
	}
	int getCount() const { return mCount; }
	int getPrice() const { return mPrice; }
	const char* getName() const override { return mName; }

	bool isMe(string name) const override { return string(mName) == name; }

	void setPrice(int price) { mPrice = price; }
};