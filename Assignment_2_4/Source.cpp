#include <iostream>
#include <fstream>
#include "StudentManager.h"

using namespace std;

int main() {

	StudentManager studentManager("information.txt");
	studentManager.printAll(); // The whole output once.

	cout << "\nThe oldest one is" << endl; // // And print oldest one.
	studentManager.printOldestStudent(); 

	return EXIT_SUCCESS;
}