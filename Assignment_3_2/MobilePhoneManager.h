#pragma once

class MobilePhoneEntry {
public:

	enum class PROP { NAME, BRAND, PRICE };

	MobilePhoneEntry(char name[], char brand[], int price);

	const static int NAME_SIZE = 128, BRAND_SIZE = 128, PRICE_MAX = 1000000;

	const char* getName() const;
	void setName(char name[]);

	const char* getBrand() const;
	void setBrand(char brand[]);

	int getPrice() const;
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

	void insertEntry(char name[], char brand[], int price, int idx);
	int searchEntry(char name[]);
	void updateEntry(int idx, char newName[], char brand[], int price);
	void deleteEntry(int idx);

	void sort(MobilePhoneEntry::PROP sortKey);

	void displayAll() const;
	void reverseAll();

	MobilePhoneEntry* at(int idx);

	int getSize() const;


private:

	MobilePhoneEntry* swap(MobilePhoneEntry*& a, MobilePhoneEntry*& b);

	int mSize;

	MobilePhoneEntry* mHead;
	MobilePhoneEntry* mTail;


};