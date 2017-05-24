#include <iostream>

#include "MobilePhoneMenu.h"

using namespace std;

int main() {

	MobilePhoneMenu menu_root;

	cout << "********************************************" << endl;
	cout << "S T A R T" << endl;
	cout << "********************************************" << endl << endl;
	// print out menu list and recieve menu number to process.
	int input;
	do {
		menu_root.printChoice();
		try {
			input = menu_root.input();
		} catch (const exception& e) { // If problems occur during processing, re-enter them.
			cerr << e.what() << endl;
			input = 1;
			continue;
		}
	} while (input);


	return EXIT_SUCCESS;
}