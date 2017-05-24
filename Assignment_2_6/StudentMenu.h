#pragma once
#include <iostream>

#include "myString.h"
#include "StudentManager.h"

// =¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý    Composite pattern for `Menu Interface`    ¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=¡ý=
// A fundamental menu class.
class BaseMenu {
	static const size_t TITLE_SIZE = 256;
	char mTitle[TITLE_SIZE]; // The name to be displayed in the menu.
public:
	virtual ~BaseMenu() {}

	BaseMenu(char title[]) {
		if (my_len(title) > TITLE_SIZE)
			throw std::invalid_argument("[!] Error. title length is invalid range");
		my_cpy(mTitle, title);
	}

	virtual void command() = 0;	// What should be done when a menu is selected.
	const char* getTitle() { return mTitle; }
	BaseMenu* next = NULL;
};

// Pseudo linked list for menus.
class BaseMenuList {
public:
	BaseMenuList() {}
	~BaseMenuList() { clear(); }

	void pushBack(BaseMenu* insertItem);
	int size();
	void clear();
	BaseMenu* at(int idx);

private:
	BaseMenu* head = NULL;
};

// Middle-layer menu class.
class PopupMenu : public BaseMenu {

	BaseMenuList v;
public:
	PopupMenu(char title[]) :BaseMenu(title) {}

	virtual void command() override;	// List submenus.
	void addMenu(BaseMenu* newBaseMenu);
};



// A menu that displays students who fit the appropriate day.
class MenuPrintDays : public BaseMenu {

	StudentManager* mStudentManager;

public:
	MenuPrintDays(StudentManager& studnerManager, char title[], Student::Days day, OOP::SortKeys sortKey)
		: BaseMenu(title), mDay(day), mSortKey(sortKey), mStudentManager(&studnerManager) {}
	virtual void command() override;

private:
	Student::Days mDay;
	OOP::SortKeys mSortKey;
};
// =¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü    Composite pattern for `Menu Interface`    ¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=¡ü=


// Actual menu interface for managing students.
class StudentMenu {
	
public:
	StudentMenu(char* fileName);
	~StudentMenu() {};

	void start() { mMenu_main->command();  }	
	
private:
	PopupMenu* mMenu_main;	// Root of menu layers.
	StudentManager mStudentManager;
};