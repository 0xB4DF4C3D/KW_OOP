#pragma once

#include "MobilePhoneManager.h"

// Interface menu to be finally viewed by the user.
class MobilePhoneMenu {

	// The manager class to manage from the menu.
	MobilePhoneManager mMobilePhoneManager;
	
	// Menu keys.
	enum emMenu {
		INSERT_BEGIN = 1, INSERT_LAST, INSERT_POS,
		DELETE, UPDATE, SEARCH,
		SORT_PRICE,
		DISPLAY, REVERSE, EXIT,
		MENU_MAX // Value for automatically managing menu keys.
	};

	// Key to determine position when inserting.
	enum class emPosition { BEGIN, LAST, POS };

public:

	void printChoice();
	int input();

private:
	void menu_insert(emPosition pos);
	void menu_delete();
	void menu_update();
	void menu_search();
	void menu_sort(MobilePhoneEntry::PROP sortKey);
	void menu_display();
	void menu_reverse();

	static const char* mMenuTitles[MENU_MAX - 1];

};

