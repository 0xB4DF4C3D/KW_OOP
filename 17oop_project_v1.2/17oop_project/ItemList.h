#pragma once

#include "ItemNode.h"

class ItemList 
{
private:
	Node*		iRoot;
	ofstream*	fout;

public:
	ItemList(ofstream* fout);
	~ItemList();
	Node* deleteNode(string name);

	ItemNode* getLast() const;
	Node* getRoot() const { return iRoot; }

	// Get item whose name match. and 
	// if want, get previous node too.
	ItemNode* getNode(string name, ItemNode** prevNode = NULL) const;

	// Return current list elements as vector.
	vector<ItemNode*> getVector();

	void addItem(ItemNode* newNode);
};