#pragma once

#include "MobilePhoneManager.h"

class MobilePhoneMenu {

	MobilePhoneManager mMobilePhoneManager;
	
	enum emMenu {
		INSERT_BEGIN = 1, INSERT_LAST, INSERT_POS,
		DELETE, UPDATE, SEARCH,
		SORT_PRICE,
		DISPLAY, REVERSE, EXIT,
		MENU_MAX
	};

	enum class emPosition { BEGIN, LAST, POS };

public:
	MobilePhoneMenu();
	~MobilePhoneMenu();

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

