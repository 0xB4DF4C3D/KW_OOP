#include <iostream>

#include "ItemManager.h"

using namespace std;

int main() {

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ItemManager itemManager("input.txt");
	itemManager.printResult();
	return EXIT_SUCCESS;
}