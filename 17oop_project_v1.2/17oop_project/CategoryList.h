#pragma once

#include "CategoryNode.h"

class CategoryList
{
private:
	Node*		cRoot;
	ofstream*	fout;


public:
	CategoryList(ofstream* fout);

	void push_back(CategoryNode* newNode);
	void push_item(CategoryNode* category, Node* newNode);
	
	bool isIn(CategoryNode* category, string name);

	CategoryNode* getLast() const;
	CategoryNode* getNode(string name, CategoryNode** prevNode = NULL) const;
	Node* getRoot() const { return cRoot; }

	bool deleteNode(string name);
};