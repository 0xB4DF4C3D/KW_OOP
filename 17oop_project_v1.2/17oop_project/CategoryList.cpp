#include "CategoryList.h"

#include "ItemNode.h"

CategoryNode * CategoryList::getNode(string name, CategoryNode** prevNode) const {
	CategoryNode* targetNode = static_cast<CategoryNode*>(cRoot);

	if (prevNode != NULL)
		*prevNode = static_cast<CategoryNode*>(cRoot);
	if (targetNode == NULL)
		return NULL;

	while (targetNode != NULL) {
		if (targetNode->isMe(name))
			return targetNode;
		if (prevNode != NULL)
			*prevNode = targetNode;
		targetNode = static_cast<CategoryNode*>(targetNode->getNext());
	}

	return NULL;
}

bool CategoryList::deleteNode(string name) {

	CategoryNode* targetNode, *targetPrevNode;
	targetNode =  getNode(name, &targetPrevNode);
	if (targetNode == NULL)
		return false;
	targetPrevNode->setNext(targetNode->getNext());
	delete targetNode;

	return true;
}

CategoryNode * CategoryList::getLast() const {
	Node* lastNode;
	for (lastNode = cRoot; lastNode->getNext() != NULL; lastNode = lastNode->getNext());
	return static_cast<CategoryNode*>(lastNode);
}

CategoryList::CategoryList(ofstream* fout) {
	this->fout = fout;
	cRoot = NULL;
}

void CategoryList::push_back(CategoryNode* newNode) {

	if (cRoot == NULL || strcmp(static_cast<CategoryNode*>(cRoot)->getName(), newNode->getName()) >= 0) {
		newNode->setNext(cRoot);
		cRoot = newNode;
	}
	else {
		CategoryNode* currentNode = static_cast<CategoryNode*>(cRoot);

		while (currentNode->getNext() != NULL &&
			strcmp(static_cast<CategoryNode*>(currentNode->getNext())->getName(), newNode->getName()) < 0) {

			currentNode = static_cast<CategoryNode*>(currentNode->getNext());
		}

		newNode->setNext(currentNode->getNext());
		currentNode->setNext(newNode);
	}
}

void CategoryList::push_item(CategoryNode* category, Node* newNode) {

	if (category->getDown() == NULL || strcmp(category->getName(), static_cast<ItemNode*>(newNode)->getName()) >= 0) {
		newNode->setDown(category->getDown());
		newNode->setUp(category);
		if (category->getDown() != NULL)
			category->getDown()->setUp(newNode);
		category->setDown(newNode);
	}
	else {
		CategoryNode* currentNode = category;

		while (currentNode->getDown() != NULL &&
			strcmp(static_cast<CategoryNode*>(currentNode->getDown())->getName(), static_cast<ItemNode*>(newNode)->getName()) < 0) {

			currentNode = static_cast<CategoryNode*>(currentNode->getDown());
		}

		newNode->setDown(currentNode->getDown());
		newNode->setUp(currentNode);
		if (currentNode->getDown() != NULL)
			currentNode->getDown()->setUp(newNode);
		currentNode->setDown(newNode);
	}
}

bool CategoryList::isIn(CategoryNode * category, string name) {
	ItemNode* currentItem = static_cast<ItemNode*>(category->getDown());

	while (currentItem->getDown() != NULL) {
		if (currentItem->isMe(name))
			return true;
		currentItem = static_cast<ItemNode*>(currentItem->getDown());
	}

	return false;
}
