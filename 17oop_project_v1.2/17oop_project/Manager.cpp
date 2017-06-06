#include "Manager.h"

#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <string>

Manager::Manager() {
	fout.open("log.txt", ios::app);
	cList = new CategoryList(&fout);
	iList = new ItemList(&fout);
}

Manager::~Manager() {
	delete cList;
	delete iList;
}

void Manager::run(const char* fileName) {
	ifstream fin;
	fin.open(fileName);

	if (!fin) {
		cout << "[OPEN]" << endl << "error" << endl;
		return;
	}

	char cmd[64] = { 0 };
	char arg[64] = { 0 };

	bool isWork = true, hasResult = true;

	while (!fin.eof()) {
		fin >> cmd;
		fin.getline(arg, 64);

		cout << "[" << cmd << "]" << endl;
		fout << "[" << cmd << "]" << endl;

		if (!strcmp(cmd, "LOAD")) {
			isWork = LOAD(); hasResult = false;
		} else if (!strcmp(cmd, "ADD")) {
			isWork = ADD(arg); hasResult = false;
		} else if (!strcmp(cmd, "MODIFY")) {
			isWork = MODIFY(arg); hasResult = false;
		} else if (!strcmp(cmd, "SELL")) {
			isWork = SELL(arg); hasResult = false;
		} else if (!strcmp(cmd, "DELETE")) {
			isWork = DELETE(arg); hasResult = false;
		} else if (!strcmp(cmd, "SEARCH")) {
			isWork = SEARCH(arg); hasResult = true;
		} else if (!strcmp(cmd, "PRINT")) {
			isWork = PRINT(arg); hasResult = true;
		} else if (!strcmp(cmd, "MANAGE")) {
			isWork = MANAGE(arg); hasResult = true;
		} else if (!strcmp(cmd, "SALES")) {
			isWork = SALES(arg); hasResult = true;
		} else if (!strcmp(cmd, "SAVE")) {
			isWork = SAVE(); hasResult = false;
		} else { isWork = false; }

		if (isWork == false) {
			cout << "error" << endl << endl;
			fout << "error" << endl << endl;
		} else {
			if (hasResult == false) {
				cout << "success" << endl << endl;
				fout << "success" << endl << endl;
			}
		}
	}

	fin.close();
}

bool Manager::LOAD() {
	char cLineBuf[128];
	string lineBuf;
	vector<string> tokens;

	ifstream itemFile("item.txt");

	if (!itemFile.is_open()) // If file can not be opened, simply skip it.
		return true;

	while (!itemFile.eof()) {
		getline(itemFile, lineBuf);
		strcpy(cLineBuf, lineBuf.c_str());
		ADD(cLineBuf);
	}

	itemFile.close();
	return true;
}

bool Manager::ADD(char* arg) {
	vector<string> tokens;
	tokenize(string(arg), tokens, " ");

	if (tokens.size() == 2) { // If two arguments, add to existing item.

		ItemNode* currentItem = iList->getNode(tokens[0]);
		int count = atoi(tokens[1].c_str());
		if (currentItem == NULL || count < 1) // // If item or number to added is not appropriate.
			return false;

		currentItem->addCount(count);

	} else if (tokens.size() == 4) { // If four arguments, add new item.

		const char* itemName = tokens[0].c_str();
		const char* categoryName = tokens[1].c_str();

		// Check that price and number are appropriate.
		int count = atoi(tokens[2].c_str());
		int price = atoi(tokens[3].c_str());
		if (count < 1 || price < 1)
			return false;

		// First, check whether there is category to which item to be added belongs.
		CategoryNode* currentCategory = cList->getNode(tokens[1]);
		if (currentCategory == NULL) {

			// If not, create new one and 
			CategoryNode* newCategoryNode = new CategoryNode(categoryName);
			cList->addCategory(newCategoryNode);
			// add item to it.
			ItemNode* newItemNode = new ItemNode(itemName, count, price);
			cList->addItem(newCategoryNode, newItemNode);
			iList->addItem(newItemNode);
		} else {

			// If Item to added is already there.
			if (cList->isIn(currentCategory, tokens[0]))
				return false;

			// Add item to it.
			ItemNode* newItemNode = new ItemNode(itemName, count, price);
			cList->addItem(currentCategory, newItemNode);
			iList->addItem(newItemNode);
		}

	}
	return true;
}

bool Manager::MODIFY(char* arg) {
	vector<string> tokens;
	tokenize(string(arg), tokens, " ");

	ItemNode* targetNode = iList->getNode(tokens[0]);
	int price = atoi(tokens[1].c_str());

	// If name or price is wrong.
	if (targetNode == NULL || price < 1)
		return false;

	targetNode->setPrice(price);
	return true;
}

bool Manager::SELL(char* arg) {
	vector<string> tokens;
	tokenize(string(arg), tokens, " ");


	ItemNode* targetNode = iList->getNode(tokens[0]);
	int sellAmount = atoi(tokens[1].c_str());

	// If name or amount is wrong.
	if (targetNode == NULL || sellAmount < 1)
		return false;

	// subCount method returns false when quantity of goods is negative, 
	// without performing any operation.
	bool isWork = targetNode->subCount(sellAmount);

	// Only records when item is sold successfully.
	if (isWork) {
		ofstream sellFile("sell.txt", ios::app);
		sellFile << targetNode->getName() << " " << sellAmount * targetNode->getPrice() << endl;
		sellFile.close();
	}

	return isWork;
}

bool Manager::DELETE(char* arg) {
	vector<string> tokens;
	tokenize(string(arg), tokens, " ");

	// deleteNode method returns NULL if deletion fails. Or
	// if successful. Returns above node of deleted node.
	Node* deletedAboveNode = iList->deleteNode(tokens[0]);

	if (deletedAboveNode == NULL) {
		return false;

		// If deleted node was last item in category
	} else if (deletedAboveNode->getDown() == NULL) {

		// Clear category and return true.
		if (cList->deleteNode(deletedAboveNode->getName()))
			return true;
		else
			assert(!"[!] Error. Bug in the Manager::DELETE(char* arg)."); // If it is false, there is problem with code.
	}

	return true;
}

bool Manager::SEARCH(char* arg) {
	vector<string> tokens;
	tokenize(string(arg), tokens, " ");

	// Determine method of SEARCH.
	function<bool(ItemNode* node, string s)> customComp;
	if (tokens[0].size() == 1) { // If only one letter is entered

		// True if first letter matches.
		customComp = [](ItemNode* node, string word)->bool { return node->getName()[0] == word.c_str()[0]; };
	} else {

		// True if all word contained.
		customComp = [](ItemNode* hayStackNode, string needle)->bool { return string(hayStackNode->getName()).find(needle) != string::npos; };
	}

	// Select items that meet condition.
	ItemNode* currentNode = static_cast<ItemNode*>(iList->getRoot());
	vector<ItemNode*> searchedNodes;
	while (currentNode != NULL) {
		if (customComp(currentNode, tokens[0]))
			searchedNodes.push_back(currentNode);
		currentNode = static_cast<ItemNode*>(currentNode->getNext());
	}

	// If there are no items matching condition
	if (searchedNodes.size() == 0) {
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
		return true;
	}

	// Sort by name.
	sort(searchedNodes.begin(), searchedNodes.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });

	// Output items found.
	for (const auto& currentNode : searchedNodes)
		printItem(currentNode);

	cout << endl;
	fout << endl;

	return true;
}

bool Manager::PRINT(char* arg) {
	if (strcmp(arg, "\0") == 0) { // If there is no argument.
		Node* currentCategory = cList->getRoot();

		// If there are no items yet.
		if (currentCategory->getDown() == NULL) {
			cout << "No Result" << endl << endl;
			fout << "No Result" << endl << endl;
			return true;
		}

		// Traverse categories and output items.
		while (currentCategory != NULL) {
			cout << "<" << currentCategory->getName() << ">" << endl;
			fout << "<" << currentCategory->getName() << ">" << endl;

			ItemNode* currentItem = static_cast<ItemNode*>(currentCategory->getDown());
			while (currentItem != NULL) {
				printItem(currentItem, false);
				currentItem = static_cast<ItemNode*>(currentItem->getDown());
			}
			currentCategory = currentCategory->getNext();
		}
	} else {
		vector<string> tokens;
		tokenize(string(arg), tokens, " ");

		Node* currentCategory = cList->getNode(tokens[0]);

		assert((currentCategory->getDown(), "[!] Error. Bug in the Manager::PRINT(char* arg).")); // If it is false, there is problem with code.

		// Traverse that category and output its items.
		cout << "<" << currentCategory->getName() << ">" << endl;
		fout << "<" << currentCategory->getName() << ">" << endl;
		ItemNode* currentItem = static_cast<ItemNode*>(currentCategory->getDown());
		while (currentItem != NULL) {
			printItem(currentItem, false);
			currentItem = static_cast<ItemNode*>(currentItem->getDown());
		}
	}

	cout << endl;
	fout << endl;
	return true;
}

bool Manager::MANAGE(char* arg) {
	vector<string> tokens;
	tokenize(string(arg), tokens, " ");

	int upperLimit = atoi(tokens[0].c_str()), addAmount = 0;

	if (tokens.size() == 2)
		addAmount = atoi(tokens[1].c_str());

	// If upper limit and amount to add are not appropriate.
	if (upperLimit < 1 || (tokens.size() == 2 && addAmount < 1))
		return false;

	// Select items that meet condition.
	vector<ItemNode*> searchedNodes;
	ItemNode* currentNode = static_cast<ItemNode*>(iList->getRoot());
	while (currentNode != NULL) {
		if (currentNode->getCount() <= upperLimit) {
			currentNode->addCount(addAmount);
			searchedNodes.push_back(currentNode);
		}
		currentNode = static_cast<ItemNode*>(currentNode->getNext());
	}

	// If there are no items matching condition
	if (searchedNodes.size() == 0) {
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
		return true;
	}

	// Sort by name.
	sort(searchedNodes.begin(), searchedNodes.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });

	// Output items found.
	for (const auto& currentNode : searchedNodes)
		printItem(currentNode);

	cout << endl;
	fout << endl;
	return true;
}

bool Manager::SALES(char* arg) {
	vector<string> argTokens, lineTokens;
	string lineBuf;
	map<string, int> saleMap;

	tokenize(string(arg), argTokens, " ");
	size_t upperRank = atoi(argTokens[0].c_str());

	if (upperRank < 1) return false;

	// Handle sellFile.
	ifstream sellFile("sell.txt");
	while (!sellFile.eof()) {
		getline(sellFile, lineBuf);
		tokenize(lineBuf, lineTokens, " ");

		// Empty line exception handling.
		if (lineTokens.size() == 0)
			break;

		// Get sum of sales by item.
		if (saleMap.find(lineTokens[0]) == saleMap.end())
			saleMap[lineTokens[0]] = atoi(lineTokens[1].c_str());
		else
			saleMap[lineTokens[0]] += atoi(lineTokens[1].c_str());

		lineTokens.clear();
	}
	sellFile.close();

	// If there are no items sold.
	if (saleMap.size() == 0) {
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
		return true;
	}

	// In this case, only sales amount is important, and
	// number is not important.
	for (const auto& sellEntry : saleMap) {
		ItemNode* newNode = new ItemNode(sellEntry.first.c_str(), -1, sellEntry.second);
		vItem.push_back(newNode);
	}

	// Sort first by name, then by price.
	sort(vItem.begin(), vItem.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });
	sort(vItem.begin(), vItem.end(), [](ItemNode* a, ItemNode* b) {return a->getPrice() > b->getPrice(); });

	// Find sales by item and print and calculate sum.
	int currentRank = 1, currentIdx = 0;
	do {
		cout << "    " << vItem[currentIdx]->getName() << " - " << vItem[currentIdx]->getPrice() << endl;
		fout << vItem[currentIdx]->getName() << " - " << vItem[currentIdx]->getPrice() << endl;
		
		// Part to handle duplicated price.
		currentIdx++;
		if (currentIdx < vItem.size() - 1 && vItem[currentIdx]->getPrice() != vItem[currentIdx + 1]->getPrice())
			currentRank++;

	} while (currentRank <= upperRank && currentIdx < vItem.size());

	// Calculate the total sales.
	int totalPrice = accumulate(vItem.begin(), vItem.end(), 0, [](int sum, ItemNode* node) {return sum + node->getPrice(); });
	cout << "    " << "Total - " << totalPrice;
	cout << endl << endl;
	fout << "Total - " << totalPrice;
	fout << endl << endl;

	// Delete allocated memory.
	for (auto& i : vItem)
		delete i;
	vItem.clear();

	return true;
}

bool Manager::SAVE() {

	ofstream itemFile("item.txt", ios::trunc);

	// Vectorize list of items.
	auto itemVector = iList->getVector();

	// First sort by name, then sort by category.
	sort(itemVector.begin(), itemVector.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });
	sort(itemVector.begin(), itemVector.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getCategory()->getName(),b->getCategory()->getName()) < 0; });

	// Save current item information in file.
	for (const auto& item : itemVector) {
		itemFile << item->getName() << " ";
		itemFile << item->getCategory()->getName() << " ";
		itemFile << item->getCount() << " ";
		itemFile << item->getPrice() << endl;
	}
	itemFile.close();
	return true;
}

void Manager::tokenize(const string& str, vector<string>& tokens, const string& delimiters) {

	string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {

		tokens.push_back(str.substr(lastPos, pos - lastPos));

		lastPos = str.find_first_not_of(delimiters, pos);

		pos = str.find_first_of(delimiters, lastPos);
	}
}

void Manager::printItem(ItemNode* item, bool withCategory) {
	cout << "    " << item->getName() << " ";
	if (withCategory) cout << item->getCategory()->getName() << " ";
	cout << item->getCount() << " ";
	cout << item->getPrice() << endl;

	fout << item->getName() << " ";
	if (withCategory) fout << item->getCategory()->getName() << " ";
	fout << item->getCount() << " ";
	fout << item->getPrice() << endl;
}
