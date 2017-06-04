#include "ItemManager.h"

#include <fstream>
#include <iostream>

using namespace std;

ItemManager::ItemManager(const char* fileName) {
	ifstream inputFile(fileName);
	Follower* newFollower;
	 
	char word[BUFSIZ]; // Temporary word buffer.

	// First, make a complete list of words using the linked list structure.
	while (!inputFile.eof()) {
		inputFile >> word;
		newFollower = new Follower(word);
		mAllWords.insert(INT_MAX, newFollower); // infinity. In other words, add a new Node at the end.
	}

	mSet = nullptr; 
}


ItemManager::~ItemManager() {
	delete[] mSet;
}

void ItemManager::makeSet() {

	Follower* currentFollower;
	ItemList tempItemList;
	int idx = 0;

	// Add each element from the mAllWords to the tempItemList.
	tempItemList.insert(INT_MAX, new Follower(mAllWords.at(idx++)->getWord()));
	do {
		currentFollower = mAllWords.at(idx++);

		// Do not add any words that already exist in tempItemList.
		if (tempItemList.isExist(currentFollower->getWord()) == false)
			tempItemList.insert(INT_MAX, new Follower(currentFollower->getWord()));
		
	} while (mAllWords.at(idx + 1) != nullptr);

	// Create a Word set from a list of unique words in tempItemList.
	mSetSize = tempItemList.size();
	mSet = new ItemList[mSetSize];
	for (int idx = 0; idx < mSetSize; idx++)
		mSet[idx].setWord(tempItemList.at(idx)->getWord());
}

void ItemManager::makeLink() {

	makeSet(); // Get a list of unique words.

	Follower* theFollower;
	ItemList* currentItemList;
	int AllWordSize = mAllWords.size();
	char* currentWord;

	// Create a link with the name of each Head of ItemList.
	currentWord = mAllWords.at(0)->getWord();
	currentItemList = find(mSet, mSetSize, currentWord);
	for (int idx = 1; idx < AllWordSize; idx++) {

		currentWord = mAllWords.at(idx)->getWord();

		// If the follower already exists in the link, increase the count
		if (currentItemList->isExist(currentWord) == true) {
			theFollower = currentItemList->find(currentWord);
			theFollower->setCount(theFollower->getCount() + 1);
		} else { // If not, add a new one.
			currentItemList->insert(INT_MAX, new Follower(currentWord));
			currentItemList->setSize(currentItemList->getSize() + 1);
		}

		// Go to the next ItemList.
		currentItemList = find(mSet, mSetSize, currentWord);
	}

}

void ItemManager::printResult() {

	makeLink(); // Get links between words.

	Follower* theFollower;
	int theItemListSize;


	// Traverse Items.
	for (int i = 0; i < mSetSize; i++) {

		// Print the Item name first.
		cout << mSet[i].getWord() << ": ";

		// And print the names and counts of the followers that follow.
		theItemListSize = mSet[i].getSize();
		for (int j = 0; j < theItemListSize-1; j++) {
			theFollower = mSet[i].at(j);
			cout << theFollower->getWord() << "(" << theFollower->getCount() << "), ";
		}

		// The last is processed separately to handle comma.
		theFollower = mSet[i].at(theItemListSize-1);
		cout << theFollower->getWord() << "(" << theFollower->getCount() << ")" << endl;

	}
}

ItemList* ItemManager::find(ItemList* itemList, int itemListSize, const char* word) {

	// From the list of itemList given,
	// check that there is an Item corresponding to the given word.
	for (int idx = 0; idx < itemListSize; idx++) {
		if (strcmp(itemList[idx].getWord(), word) == 0)
			return &itemList[idx]; // If yes, return it.
	}

	return nullptr; // If not, return nullptr.
}
