#include <iostream>

#include "StudentMenu.h"

using namespace std;

int main() {

	StudentMenu studentMenu("ScoreList.txt");

	studentMenu.start();

	return EXIT_SUCCESS;
}