#pragma once

#include "AddressInfoManager.h"

class AddressInfoMenu {

	AddressInfoManager mManager;

	enum Menu {
		SHOW_PEOPLE = 1, SHOW_HOUSE, CHANGE_NAME, CHANGE_ADDRESS, QUIT,
		MENU_MAX
	};

	enum class Entity {
		PERSON, HOUSE
	};

	static const char* MenuTitle[MENU_MAX - 1];

public:
	AddressInfoMenu(const char* fileName);
	~AddressInfoMenu();

	void printChoice();
	int input();

private:
	void menu_show(Entity showedEntity);
};

