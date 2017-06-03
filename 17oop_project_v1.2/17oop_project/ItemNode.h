#pragma once

#include "Node.h"

class ItemNode : public Node
{
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

	bool isMe(string name) const { return string(mName) == name; }
	
	const char* getName() const { return mName; }
	int getCount() const { return mCount; }
	int getPrice() const { return mPrice; }
	Node* getCategory() { 
		Node* myCategory = this;
		while (myCategory->getUp() != NULL)
			myCategory = myCategory->getUp();
		return myCategory;
	}
	string getType() const override { return "item"; }

	void addCount(int amount) { mCount += amount; }
	bool subCount(int amount) { if (amount > mCount) return false; else mCount -= amount; return true; }

	void setPrice(int price) { mPrice = price; }
};