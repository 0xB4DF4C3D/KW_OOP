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
	/* write your code */
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
	string lineBuf;
	char cLineBuf[128];
	vector<string> tokens;

	ifstream itemFile("item.txt");

	if (!itemFile.is_open())
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
	string s_arg(arg);
	vector<string> tokens;
	tokenize(s_arg, tokens, " ");

	if (tokens.size() == 2) {
		ItemNode* currentItem = static_cast<ItemNode*>(iList->getNode(tokens[0]));
		int count = atoi(tokens[1].c_str());

		if (currentItem == NULL || count < 1)
			return false;

		currentItem->addCount(count);
	} else if (tokens.size() == 4) {
		CategoryNode* currentCategory = cList->getNode(tokens[1]);
		if (currentCategory == NULL) {
			CategoryNode* newCategoryNode = new CategoryNode(tokens[1].c_str());
			cList->push_back(newCategoryNode);

			int count = atoi(tokens[2].c_str());
			int price = atoi(tokens[3].c_str());

			if (count < 1 || price < 1)
				return false;

			ItemNode* newItemNode = new ItemNode(tokens[0].c_str(), count, price);
			cList->push_item(newCategoryNode, newItemNode);
			iList->push_back(newItemNode);

		} else {

			if (cList->isIn(currentCategory, tokens[0]))
				return false;

			ItemNode* newItemNode = new ItemNode(tokens[0].c_str(), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()));

			cList->push_item(currentCategory, newItemNode);
			iList->push_back(newItemNode);
		}

	}
	return true;
}

bool Manager::MODIFY(char* arg) {
	string s_arg(arg);
	vector<string> tokens;
	tokenize(s_arg, tokens, " ");

	ItemNode* targetNode = iList->getNode(tokens[0]);

	if (targetNode == NULL)
		return false;

	targetNode->setPrice(atoi(tokens[1].c_str()));
	return true;
}

bool Manager::SELL(char* arg) {
	string s_arg(arg);
	vector<string> tokens;
	tokenize(s_arg, tokens, " ");

	ItemNode* targetNode = iList->getNode(tokens[0]);

	if (targetNode == NULL)
		return false;

	int sellAmount = atoi(tokens[1].c_str());

	if (sellAmount < 1)
		return false;

	bool isWork = targetNode->subCount(sellAmount);

	if (isWork) {
		ofstream sellFile("sell.txt", ios::app);
		sellFile << targetNode->getName() << " " << sellAmount * targetNode->getPrice() << endl;
		sellFile.close();
	}

	return isWork;
}

bool Manager::DELETE(char* arg) {
	string s_arg(arg);
	vector<string> tokens;
	tokenize(s_arg, tokens, " ");

	Node* deletedAboveNode = iList->deleteNode(tokens[0]);

	if (deletedAboveNode == NULL) {
		return false;
	} else if (deletedAboveNode->getType() == "category") {
		if (cList->deleteNode(static_cast<CategoryNode*>(deletedAboveNode)->getName()))
			return false;
	}

	return true;
}

bool Manager::SEARCH(char* arg) {
	string s_arg(arg);
	vector<string> tokens;
	tokenize(s_arg, tokens, " ");

	vector<ItemNode*> searchedNodes;

	function<bool(ItemNode* node, string s)> customComp;

	ItemNode* currentNode = static_cast<ItemNode*>(iList->getRoot());

	if (tokens[0].size() == 1)
		customComp = [](ItemNode* node, string word)->bool { return node->getName()[0] == word.c_str()[0]; };
	else
		customComp = [](ItemNode* hayStackNode, string needle)->bool { return string(hayStackNode->getName()).find(needle) != string::npos; };

	while (currentNode != NULL) {
		if (customComp(currentNode, tokens[0]))
			searchedNodes.push_back(currentNode);
		currentNode = static_cast<ItemNode*>(currentNode->getNext());
	}

	if (searchedNodes.size() == 0) {
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
		return true;
	}

	sort(searchedNodes.begin(), searchedNodes.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });

	for (const auto& currentNode : searchedNodes) {
		cout << "    " << currentNode->getName() << " ";
		cout << static_cast<ItemNode*>(currentNode->getCategory())->getName() << " ";
		cout << currentNode->getCount() << " ";
		cout << currentNode->getPrice() << endl;


		fout << currentNode->getName() << " ";
		fout << static_cast<ItemNode*>(currentNode->getCategory())->getName() << " ";
		fout << currentNode->getCount() << " ";
		fout << currentNode->getPrice() << endl;
	}
	cout << endl;
	fout << endl;

	return true;
}

bool Manager::PRINT(char* arg) {
	if (strcmp(arg, "\0") == 0) {
		CategoryNode* currentCategory = static_cast<CategoryNode*>(cList->getRoot());

		if (currentCategory->getDown() == NULL) {
			cout << "No Result" << endl << endl;
			fout << "No Result" << endl << endl;
			return true;
		}

		while (currentCategory != NULL) {
			cout << "<" << currentCategory->getName() << ">" << endl;
			fout << "<" << currentCategory->getName() << ">" << endl;

			ItemNode* currentItem = static_cast<ItemNode*>(currentCategory->getDown());
			while (currentItem != NULL) {
				cout << "    " << currentItem->getName() << " ";
				cout << currentItem->getCount() << " ";
				cout << currentItem->getPrice() << endl;

				fout << currentItem->getName() << " ";
				fout << currentItem->getCount() << " ";
				fout << currentItem->getPrice() << endl;

				currentItem = static_cast<ItemNode*>(currentItem->getDown());
			}
			currentCategory = static_cast<CategoryNode*>(currentCategory->getNext());
		}

	} else {
		string s_arg(arg);
		vector<string> tokens;
		tokenize(s_arg, tokens, " ");

		CategoryNode* currentCategory = static_cast<CategoryNode*>(cList->getNode(tokens[0]));

		if (currentCategory->getDown() == NULL) {
			cout << "No Result" << endl << endl;
			fout << "No Result" << endl << endl;
			return true;
		}

		cout << "<" << currentCategory->getName() << ">" << endl;
		fout << "<" << currentCategory->getName() << ">" << endl;

		ItemNode* currentItem = static_cast<ItemNode*>(currentCategory->getDown());
		while (currentItem != NULL) {
			cout << currentItem->getName() << " ";
			cout << currentItem->getCount() << " ";
			cout << currentItem->getPrice() << endl << endl;


			fout << currentItem->getName() << " ";
			fout << currentItem->getCount() << " ";
			fout << currentItem->getPrice() << endl << endl;

			currentItem = static_cast<ItemNode*>(currentItem->getDown());
		}
	}
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::MANAGE(char* arg) {
	string s_arg(arg);
	vector<string> tokens;
	tokenize(s_arg, tokens, " ");

	int upperLimit = atoi(tokens[0].c_str()), addAmount = 0;

	if (tokens.size() == 2)
		addAmount = atoi(tokens[1].c_str());

	if (upperLimit < 1 || (tokens.size() == 2 && addAmount < 1))
		return false;

	vector<ItemNode*> searchedNodes;

	ItemNode* currentNode = static_cast<ItemNode*>(iList->getRoot());

	while (currentNode != NULL) {
		if (currentNode->getCount() <= upperLimit) {
			currentNode->addCount(addAmount);
			searchedNodes.push_back(currentNode);
		}
		currentNode = static_cast<ItemNode*>(currentNode->getNext());
	}

	if (searchedNodes.size() == 0) {
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
		return true;
	}

	sort(searchedNodes.begin(), searchedNodes.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });

	for (const auto& currentNode : searchedNodes) {
		cout << "    " << currentNode->getName() << " ";
		cout << static_cast<CategoryNode*>(currentNode->getCategory())->getName() << " ";
		cout << currentNode->getCount() << " ";
		cout << currentNode->getPrice() << endl;

		fout << currentNode->getName() << " ";
		fout << static_cast<CategoryNode*>(currentNode->getCategory())->getName() << " ";
		fout << currentNode->getCount() << " ";
		fout << currentNode->getPrice() << endl;
	}
	cout << endl;
	fout << endl;

	return true;
}

bool Manager::SALES(char* arg) {
	string lineBuf;
	vector<string> argTokens, lineTokens;
	map<string, int> saleMap;

	tokenize(string(arg), argTokens, " ");
	vItem.clear();
	size_t upperRank = atoi(argTokens[0].c_str());
	if (upperRank < 1) return false;

	ifstream sellFile("sell.txt");
	while (!sellFile.eof()) {
		getline(sellFile, lineBuf);
		tokenize(lineBuf, lineTokens, " ");

		if (lineTokens.size() == 0)
			break;

		if (saleMap.find(lineTokens[0]) == saleMap.end()) {
			saleMap[lineTokens[0]] = atoi(lineTokens[1].c_str());
		} else {
			saleMap[lineTokens[0]] += atoi(lineTokens[1].c_str());
		}
		lineTokens.clear();
	}
	sellFile.close();

	if (saleMap.size() == 0) {
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
		return true;
	}

	for (const auto& sellEntry : saleMap) {
		ItemNode* newNode = new ItemNode(sellEntry.first.c_str(), -1, sellEntry.second);
		vItem.push_back(newNode);
	}

	sort(vItem.begin(), vItem.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });
	sort(vItem.begin(), vItem.end(), [](ItemNode* a, ItemNode* b) {return a->getPrice() > b->getPrice(); });

	int currentRank = 1, currentIdx = 0;
	do {
		cout << "    " << vItem[currentIdx]->getName() << " - " << vItem[currentIdx]->getPrice() << endl;
		fout << vItem[currentIdx]->getName() << " - " << vItem[currentIdx]->getPrice() << endl;
		currentIdx++;

		if (currentIdx < vItem.size() - 1 && vItem[currentIdx]->getPrice() != vItem[currentIdx + 1]->getPrice())
			currentRank++;
	} while (currentRank <= upperRank && currentIdx < vItem.size());
	int totalPrice = accumulate(vItem.begin(), vItem.end(), 0, [](int sum, ItemNode* node) {return sum + node->getPrice(); });
	cout << "    " << "Total - " << totalPrice;
	cout << endl;

	fout << "Total - " << totalPrice;
	fout << endl;
	return true;
}

bool Manager::SAVE() {

	ofstream itemFile("item2.txt", ios::trunc);

	auto itemVector = iList->getVector();

	sort(itemVector.begin(), itemVector.end(), [](ItemNode* a, ItemNode* b) {return strcmp(a->getName(), b->getName()) < 0; });
	sort(itemVector.begin(), itemVector.end(), [](ItemNode* a, ItemNode* b) {return strcmp(static_cast<CategoryNode*>(a->getCategory())->getName(), static_cast<CategoryNode*>(b->getCategory())->getName()) < 0; });

	for (const auto& item : itemVector) {
		itemFile << item->getName() << " ";
		itemFile << static_cast<ItemNode*>(item->getCategory())->getName() << " ";
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