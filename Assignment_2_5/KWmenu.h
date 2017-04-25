#pragma once

#include "KWmanager.h"
class KWmenu {

	static const size_t NUMBER_OF_MENU = 7;

public:
	KWmenu(char *fileName);
	~KWmenu();

	void printChoice();
	int input();

private:
	void menu_load();
	void menu_insert();
	void menu_update();
	void menu_delete();
	void menu_print();
	void menu_save();

	enum emMenu {
		LOAD=1, INSERT, UPDATE, DELETE, PRINT, SAVE, QUIT
	};

	char* mMenus[NUMBER_OF_MENU] = {
		"Load", "Insert", "Update", "Delete", "Print",
		"Save", "Quit"
	};

	KWmanager mKWmanager;

};

