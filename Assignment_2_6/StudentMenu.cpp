#include "StudentMenu.h"

#include "myString.h"

using namespace std;

// Add submenu.
void BaseMenuList::pushBack(BaseMenu* insertItem) {
	if (head == NULL) {
		head = insertItem;
	} else {
		BaseMenu* currentPtr;
		for (currentPtr = head; currentPtr->next != NULL; currentPtr = currentPtr->next);
		currentPtr->next = insertItem;
	}
}

// Returns number of submenus.
int BaseMenuList::size() {
	int size = 0;
	for (BaseMenu* currentPtr = head;
		currentPtr != NULL;
		currentPtr = currentPtr->next, size++);

	return size;
}

// Delete dynamically allocated submenu objects.
void BaseMenuList::clear() {
	BaseMenu* pDel = head;

	while (pDel != NULL) {
		head = head->next;
		delete pDel;

		pDel = head;
	}
	head = NULL;
}

// Functions for accessing specific submenus.
BaseMenu* BaseMenuList::at(int idx) {
	BaseMenu* currentPtr = head;
	int i;
	for (i = 0; i < idx; i++) {
		currentPtr = currentPtr->next;

		if (currentPtr == NULL)
			throw invalid_argument("[!] Error. invalid idx in BaseMenuList::at()");
	}
	return currentPtr;
}

// If it is a middle-layer menu, it list submenus.
// Then get the number.
void PopupMenu::command() {

	while (true) {
		int size = v.size();

		// List submenus.
		for (int i = 0; i < size; i++)
			cout << i + 1 << ". " << v.at(i)->getTitle() << "    ";
		cout << size + 1 << ". Cancel" << endl;

		// Enter the appropriate menu number.
		int menuNumber;
		do {
			cout << "> Input number : ";
		} while (safeNumInput(cin, menuNumber, 0, size + 1));
		cout << endl;

		// Cancel Processing part.
		if (menuNumber == size + 1)
			break;

		// Enter the selected menu.
		v.at(menuNumber - 1)->command();
	}
}

void PopupMenu::addMenu(BaseMenu* newBaseMenu) {
	v.pushBack(newBaseMenu);
}

void MenuPrintDays::command() {

	mStudentManager->printItem(mDay, mSortKey);
	cout << endl;
}


StudentMenu::StudentMenu(char* fileName) : mStudentManager(fileName){
	// Construct menu layers..

	mMenu_main = new PopupMenu("Menu");	// Root of menus.
	PopupMenu* menu_printSortedByName = new PopupMenu("Print sorted by name");		// Add a submenu named "Print sorted by name" to the root.
	mMenu_main->addMenu(menu_printSortedByName);

	PopupMenu* menu_printSortedByScore = new PopupMenu("Print sorted by score");	// Add a submenu named "Print sorted by score" to the root.
	mMenu_main->addMenu(menu_printSortedByScore);

	// Add proper action menu  to the each submenu.
	menu_printSortedByName->addMenu(new MenuPrintDays(mStudentManager, "Wednesday", Student::Days::WED, OOP::SortKeys::NAME));
	menu_printSortedByName->addMenu(new MenuPrintDays(mStudentManager, "Thursday", Student::Days::THU, OOP::SortKeys::NAME));
	menu_printSortedByName->addMenu(new MenuPrintDays(mStudentManager, "Friday", Student::Days::FRI, OOP::SortKeys::NAME));
	menu_printSortedByName->addMenu(new MenuPrintDays(mStudentManager, "Non-attendance classes", Student::Days::NON, OOP::SortKeys::NAME));

	menu_printSortedByScore->addMenu(new MenuPrintDays(mStudentManager, "Wednesday", Student::Days::WED, OOP::SortKeys::SCORE));
	menu_printSortedByScore->addMenu(new MenuPrintDays(mStudentManager, "Thursday", Student::Days::THU, OOP::SortKeys::SCORE));
	menu_printSortedByScore->addMenu(new MenuPrintDays(mStudentManager, "Friday", Student::Days::FRI, OOP::SortKeys::SCORE));
	menu_printSortedByScore->addMenu(new MenuPrintDays(mStudentManager, "Non-attendance classes", Student::Days::NON, OOP::SortKeys::SCORE));
}
