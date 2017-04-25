#pragma once

#include "MusicListManipulator.h"

// A menu interface that connects the user to the MusicListManipulator.
class MusicListMenu {

	static const size_t NUMBER_OF_MENU = 5;

public:
	MusicListMenu(char *fileName);
	~MusicListMenu();
	void printChoice(); // List possible options.
	int input(); // Receive the menu number.

private:
	void menu_insert();
	void menu_update();
	void menu_delete();
	void menu_sort();

	enum emMenu {
		INSERT = 1, UPDATE, DELETE, SORT, QUIT
	};

	char* mMenus[NUMBER_OF_MENU] = {
		"Insert", "Update", "Delete", "Sort", "Quit"
	};

	MusicListManipulator mManipulator;
};

