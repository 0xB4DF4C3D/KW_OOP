#pragma once

// This class is a node for a double linked list.
class MobilePhoneEntry {
public:

	// Attribute keys for each node.
	enum class PROP { NAME, BRAND, PRICE };

	MobilePhoneEntry(char name[], char brand[], int price);

	const static int NAME_SIZE = 128, BRAND_SIZE = 128, PRICE_MAX = 1000000;

	// Getters and setters.
	const char* getBrand() const;
	const char* getName() const;
	int getPrice() const;
	void setBrand(char brand[]);
	void setName(char name[]);
	void setPrice(int price);

	MobilePhoneEntry* mNext;
	MobilePhoneEntry* mPrev;

private:
	char mName[NAME_SIZE];
	char mBrand[BRAND_SIZE];
	int mPrice;
};


class MobilePhoneManager {
public:
	MobilePhoneManager();
	~MobilePhoneManager();

	
	void insertEntry(char name[], char brand[], int price, int idx);
	int searchEntry(char name[]);
	void updateEntry(int idx, char newName[], char brand[], int price);
	void deleteEntry(int idx);

	// Take an argument to sort by which attribute.
	void sort(MobilePhoneEntry::PROP sortKey);

	void displayAll() const;
	void reverseAll();

	MobilePhoneEntry* at(int idx);

	int getSize() const;


private:

	// A swap function for sorting internally.
	MobilePhoneEntry* swap(MobilePhoneEntry*& a, MobilePhoneEntry*& b);

	int mSize;

	MobilePhoneEntry* mHead;
	MobilePhoneEntry* mTail;


};