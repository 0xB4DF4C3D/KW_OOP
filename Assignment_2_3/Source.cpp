#include <iostream>

#include "MusicListMenu.h"

using namespace std;

int main() {

	MusicListMenu mMusicListListMenu("MusicList.txt");

	// print out menu list and recieve menu number to process.
	int input;
	do {
		mMusicListListMenu.printChoice();
		try {
			input = mMusicListListMenu.input();
		} catch (const exception& e) { // If problems occur during processing, re-enter them.
			cerr << e.what() << endl;
			input = 1;
			continue;
		}
	} while (input);

	return EXIT_SUCCESS;
}