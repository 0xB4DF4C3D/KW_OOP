#pragma once

class Item {
public:

	static const size_t NAME_SIZE = 64;
	static const size_t INFO_SIZE = 256;

	Item();
	Item(char *name, int price, int quantity);
	~Item();

	const char *getInfo(); // Convert data to appropriate structure for save.

	// Getters & Setters.
	const char* getName();
	void setName(char *name);

	int getPrice();
	void setPrice(int price);

	int getQuantity();
	void setQuantity(int quantity);

private:
	char mName[Item::NAME_SIZE];
	char mInfo[Item::INFO_SIZE];	// The value to be stored in the file.
	int mPrice, mQuantity;
};

