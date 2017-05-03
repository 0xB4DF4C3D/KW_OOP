#include "ItemManager.h"

#include <fstream>
#include <iostream>

using namespace std;

ItemManager::ItemManager(const char* fileName) {
	ifstream inputFile(fileName);
	Follower* newFollower;

	char word[BUFSIZ];

	while (!inputFile.eof()) {
		inputFile >> word;

		newFollower = new Follower();
		newFollower->setWord(word);

		mAllWords.insert(INT_MAX, newFollower);
	}

	mSet = nullptr;
}


ItemManager::~ItemManager() {
	delete[] mSet;
}

void ItemManager::makeSet() {

	Follower* currentFollower, *newFollower;
	ItemList tempItemList;
	int idx = 0;

	newFollower = new Follower();
	newFollower->setWord(mAllWords.at(idx++)->getWord());
	tempItemList.insert(INT_MAX, newFollower);
	do {
		currentFollower = mAllWords.at(idx++);
		if (tempItemList.isExist(currentFollower->getWord()) == false) {

			newFollower = new Follower();
			newFollower->setWord(currentFollower->getWord());
			tempItemList.insert(INT_MAX, newFollower);
		}
	} while (mAllWords.at(idx + 1) != nullptr);

	mSetSize = tempItemList.size();
	mSet = new ItemList[mSetSize];
	for (int idx = 0; idx < mSetSize; idx++)
		mSet[idx].setWord(tempItemList.at(idx)->getWord());
}

void ItemManager::makeLink() {

	makeSet();

	Follower* theFollower;
	ItemList* currentItemList;
	int idx, AllWordSize = mAllWords.size();
	char* currentWord;

	currentWord = mAllWords.at(0)->getWord();
	currentItemList = find(mSet, mSetSize, currentWord);
	for (int idx = 1; idx < AllWordSize; idx++) {

		currentWord = mAllWords.at(idx)->getWord();
		if (currentItemList->isExist(currentWord) == true) {
			theFollower = currentItemList->find(currentWord);
			theFollower->setCount(theFollower->getCount() + 1);
		} else {
			theFollower = new Follower();
			theFollower->setWord(currentWord);
			currentItemList->insert(INT_MAX, theFollower);
			currentItemList->setSize(currentItemList->getSize() + 1);
		}
		currentItemList = find(mSet, mSetSize, currentWord);
	}

}

void ItemManager::printResult() {

	makeLink();

	Follower* theFollower;
	int theItemListSize;

	for (int i = 0; i < mSetSize; i++) {
		cout << mSet[i].getWord() << ": ";
		theItemListSize = mSet[i].getSize();
		for (int j = 0; j < theItemListSize-1; j++) {
			theFollower = mSet[i].at(j);
			cout << theFollower->getWord() << "(" << theFollower->getCount() << "), ";
		}
		theFollower = mSet[i].at(theItemListSize-1);
		cout << theFollower->getWord() << "(" << theFollower->getCount() << ")" << endl;

	}
}

ItemList* ItemManager::find(ItemList* itemList, int itemListSize, const char* word) {

	for (int idx = 0; idx < itemListSize; idx++) {
		if (strcmp(itemList[idx].getWord(), word) == 0)
			return &itemList[idx];
	}

	return nullptr;
}
