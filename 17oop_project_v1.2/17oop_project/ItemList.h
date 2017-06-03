#pragma once

#include "ItemNode.h"

class ItemList 
{
private:
	Node*		iRoot;
	ofstream*	fout;

public:
	ItemList(ofstream* fout);


	ItemNode* getLast() const;
	ItemNode* getNode(string name, ItemNode** prevNode = NULL) const;
	Node* getRoot() const { return iRoot; }
	vector<ItemNode*> getVector();

	Node* deleteNode(string name);

	void push_back(ItemNode* newNode);
};