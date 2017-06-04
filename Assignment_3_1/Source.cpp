#include <iostream>

#include "ItemManager.h"

using namespace std;

int main() {

	ItemManager itemManager("input.txt");
	itemManager.printResult();

	return EXIT_SUCCESS;
}