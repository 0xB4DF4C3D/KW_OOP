#include "ItemList.h"

ItemList::ItemList(ofstream* fout) {
	this->fout = fout;
	iRoot = NULL;
}

ItemNode * ItemList::getLast() const {
	Node* lastNode;
	for (lastNode = iRoot; lastNode->getNext() != NULL; lastNode = lastNode->getNext());
	return static_cast<ItemNode*>(lastNode);
}

ItemNode* ItemList::getNode(string name, ItemNode** prevNode) const {
	ItemNode* targetNode = static_cast<ItemNode*>(iRoot);


	if (prevNode != NULL)
		*prevNode = static_cast<ItemNode*>(iRoot);

	if (targetNode == NULL) {
		return NULL;
	}

	while (targetNode != NULL) {
		if (targetNode->isMe(name))
			return targetNode;
		if (prevNode != NULL)
			*prevNode = targetNode;
		targetNode = static_cast<ItemNode*>(targetNode->getNext());
	}

	return NULL;
}

vector<ItemNode*> ItemList::getVector() {
	ItemNode* currentNode = static_cast<ItemNode*>(iRoot);
	vector<ItemNode*> resultVector;

	while (currentNode != NULL) {
		resultVector.push_back(currentNode);
		currentNode = static_cast<ItemNode*>(currentNode->getNext());
	}

	return resultVector;
}

Node* ItemList::deleteNode(string name) {
	ItemNode* targetPrevNode;
	Node* targetAboveNode;
	ItemNode* targetNode = getNode(name, &targetPrevNode);

	if (targetNode == NULL)
		return NULL;

	else if (targetNode->getDown() == NULL) {
		targetNode->getUp()->setDown(NULL);
	}
	else if (targetNode->getUp() == NULL) {
		targetNode->getDown()->setUp(NULL);
		iRoot = targetNode->getDown();
	}
	else {
		ItemNode* downNode = static_cast<ItemNode*>(targetNode->getDown());
		ItemNode* upNode = static_cast<ItemNode*>(targetNode->getUp());

		upNode->setDown(downNode);
		downNode->setUp(upNode);
	}

	if (targetPrevNode != targetNode)
		targetPrevNode->setNext(targetNode->getNext());
	else
		iRoot = targetNode->getNext();

	targetAboveNode = targetNode->getUp();

	delete targetNode;
	targetNode = NULL;

	return targetAboveNode;
}

void ItemList::push_back(ItemNode * newNode) {
	if (iRoot == NULL || strcmp(static_cast<ItemNode*>(iRoot)->getName(), newNode->getName()) >= 0) {
		newNode->setNext(iRoot);
		iRoot = newNode;
	}
	else {
		ItemNode* currentNode = static_cast<ItemNode*>(iRoot);

		while (currentNode->getNext() != NULL &&
			strcmp(static_cast<ItemNode*>(currentNode->getNext())->getName(), newNode->getName()) < 0) {

			currentNode = static_cast<ItemNode*>(currentNode->getNext());
		}

		newNode->setNext(currentNode->getNext());
		currentNode->setNext(newNode);
	}
}
