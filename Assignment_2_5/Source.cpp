#include <iostream>
#include "KWmenu.h"
using namespace std;

int main() {

	KWmenu kwMenu("ItemList.txt");

	do {
		kwMenu.printChoice();
	} while (kwMenu.input());

	return EXIT_SUCCESS;
}