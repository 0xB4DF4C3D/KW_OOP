#pragma once

#include "AddressInfoManager.h"

class AddressInfoMenu {

	AddressInfoManager mManager;

	enum Menu {
		SHOW_PEOPLE = 1, SHOW_HOUSE, CHANGE_NAME, CHANGE_ADDRESS, QUIT,
		MENU_MAX // Value for automatically managing menu keys.
	};

	static const char* MenuTitle[MENU_MAX - 1];

public:
	AddressInfoMenu(const std::string& fileName);
	~AddressInfoMenu();

	void printChoice();
	int input();

private:
	void menu_show(Entity::PROP showedEntity);
	void menu_change(Entity::PROP changedEntity);
};

