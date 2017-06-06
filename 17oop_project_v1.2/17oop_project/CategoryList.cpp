#include "CategoryList.h"

#include "ItemNode.h"

CategoryList::CategoryList(ofstream* fout) {
	this->fout = fout;
	cRoot = NULL;
}

CategoryList::~CategoryList() {
	Node* deletedNode = cRoot, *nextNode;

	while (deletedNode != NULL) {
		nextNode = deletedNode->getNext();
		delete deletedNode;
		deletedNode = nextNode;
	}

}

CategoryNode * CategoryList::getNode(string name, CategoryNode** prevNode) const {
	Node* targetNode = cRoot;

	while (targetNode != NULL) {
		if (targetNode->isMe(name))
			return static_cast<CategoryNode*>(targetNode);
		if (prevNode != NULL)
			*prevNode = static_cast<CategoryNode*>(targetNode);
		targetNode = targetNode->getNext();
	}

	return NULL;
}

bool CategoryList::deleteNode(string name) {

	CategoryNode* targetNode, *targetPrevNode = NULL;

	targetNode = getNode(name, &targetPrevNode);
	if (targetNode == NULL)
		return false;

	if (targetPrevNode == NULL)
		cRoot = targetNode->getNext();
	else
		targetPrevNode->setNext(targetNode->getNext());

	delete targetNode;
	return true;
}

CategoryNode * CategoryList::getLast() const {
	Node* lastNode;
	for (lastNode = cRoot; lastNode->getNext() != NULL; lastNode = lastNode->getNext());
	return static_cast<CategoryNode*>(lastNode);
}

void CategoryList::addCategory(CategoryNode* newNode) {

	// If it is first category to be inserted or name precedes first category.
	if (cRoot == NULL || strcmp(cRoot->getName(), newNode->getName()) >= 0) {
		newNode->setNext(cRoot);
		cRoot = newNode;
	} else {

		// Find node immediately before category name.
		Node* currentNode = cRoot;
		while (currentNode->getNext() != NULL && strcmp(currentNode->getNext()->getName(), newNode->getName()) < 0)
			currentNode = currentNode->getNext();

		// Inserting by re-linking  front and back nodes.
		newNode->setNext(currentNode->getNext());
		currentNode->setNext(newNode);
	}
}

void CategoryList::addItem(CategoryNode* category, Node* newNode) {

	// If it is first item to be inserted or name precedes first item.
	if (category->getDown() == NULL || strcmp(category->getDown()->getName(), newNode->getName()) >= 0) {
		newNode->setDown(category->getDown());
		newNode->setUp(category);
		if (category->getDown() != NULL)
			category->getDown()->setUp(newNode);
		category->setDown(newNode);
	} else {

		// Find node immediately before item name.
		Node* currentNode = category;
		while (currentNode->getDown() != NULL &&
			strcmp(currentNode->getDown()->getName(), newNode->getName()) 
			) {
			currentNode = currentNode->getDown();
		}

		// Inserting by re-linking front and back nodes.
		newNode->setDown(currentNode->getDown());
		newNode->setUp(currentNode);
		if (currentNode->getDown() != NULL)
			currentNode->getDown()->setUp(newNode);
		currentNode->setDown(newNode);
	}
}

bool CategoryList::isIn(CategoryNode * category, string name) {
	Node* currentItem = category->getDown();

	while (currentItem->getDown() != NULL) {
		if (currentItem->isMe(name))
			return true;
		currentItem = currentItem->getDown();
	}

	return false;
}
