#include "ItemList.h"

ItemList::ItemList(ofstream* fout) {
	this->fout = fout;
	iRoot = NULL;
}

ItemList::~ItemList() {
	Node* deletedNode = iRoot, *nextNode;

	while (deletedNode != NULL) {
		nextNode = deletedNode->getNext();
		delete deletedNode;
		deletedNode = nextNode;
	}
}

ItemNode * ItemList::getLast() const {
	Node* lastNode;
	for (lastNode = iRoot; lastNode->getNext() != NULL; lastNode = lastNode->getNext());
	return static_cast<ItemNode*>(lastNode);
}

ItemNode* ItemList::getNode(string name, ItemNode** prevNode) const {
	if (prevNode != NULL)
		*prevNode = static_cast<ItemNode*>(iRoot);

	Node* targetNode = iRoot;
	if (targetNode == NULL) {
		return NULL;
	}

	while (targetNode != NULL) {
		if (targetNode->isMe(name))
			return static_cast<ItemNode*>(targetNode);
		if (prevNode != NULL)
			*prevNode = static_cast<ItemNode*>(targetNode);
		targetNode = targetNode->getNext();
	}

	return NULL;
}

vector<ItemNode*> ItemList::getVector() {
	Node* currentNode = iRoot;
	vector<ItemNode*> resultVector;

	while (currentNode != NULL) {
		resultVector.push_back(static_cast<ItemNode*>(currentNode));
		currentNode = currentNode->getNext();
	}

	return resultVector;
}

Node* ItemList::deleteNode(string name) {
	ItemNode* targetPrevNode;
	Node* targetNode = getNode(name, &targetPrevNode);

	// Processing in Category List.
	if (targetNode == NULL) {						// If there is no item corresponding to name.
		return NULL;
	} else if (targetNode->getDown() == NULL) {		// If node to be deleted is lowest node.
		targetNode->getUp()->setDown(NULL);
	} else {											// Node to be deleted is located in middle.
		Node* downNode = targetNode->getDown();
		Node* upNode = targetNode->getUp();

		upNode->setDown(downNode);
		downNode->setUp(upNode);
	}

	// Processing in Item List.
	if (targetPrevNode != targetNode)
		targetPrevNode->setNext(targetNode->getNext());
	else
		iRoot = targetNode->getNext();

	Node* targetAboveNode;
	targetAboveNode = targetNode->getUp();

	delete targetNode;
	targetNode = NULL;

	return targetAboveNode;
}

void ItemList::addItem(ItemNode * newNode) {

	// If it is first item to be inserted or name precedes first item.
	if (iRoot == NULL || strcmp(iRoot->getName(), newNode->getName()) < 0) {
		newNode->setNext(iRoot);
		iRoot = newNode;
	} else {

		// Find node immediately before item name.
		Node* currentNode = iRoot;
		while (currentNode->getNext() != NULL && strcmp(currentNode->getNext()->getName(), newNode->getName()) < 0)
			currentNode = currentNode->getNext();

		// Inserting by re-linking back node.
		newNode->setNext(currentNode->getNext());
		currentNode->setNext(newNode);
	}
}
