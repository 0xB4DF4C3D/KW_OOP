#pragma once

#include "CategoryNode.h"

class CategoryList
{
private:
	Node*		cRoot;
	ofstream*	fout;

public:
	CategoryList(ofstream* fout);
	~CategoryList();
	bool deleteNode(string name);

	bool isIn(CategoryNode* category, string name);			// Check there is item that name matches in category.

	CategoryNode* getLast() const;
	Node* getRoot() const { return cRoot; }

	// Get category whose name match. and 
	// if want, get previous node too.
	CategoryNode* getNode(string name, CategoryNode** prevNode = NULL) const;

	void addCategory(CategoryNode* newNode);				// Add category.
	void addItem(CategoryNode* category, Node* newNode);	// Add item to category.
	
};