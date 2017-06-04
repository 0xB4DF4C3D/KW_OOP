#pragma once

class Land {
public:

	enum Status {
		START = -2, 
		NONE, JAPAN, KOREAN, END, // Value for automatically managing menu keys.
		NOT_INIT = 100
	};

	// Codes representing results
	enum Codes {
		NO_SOLDIER, SURROUNDED, NO_LAND_TO_OCCUPUY, SUCCESS_OCCUPUY
	};

	Land(int width, int height);
	~Land();

	// Get result and 
	// time it takes for the attacker to occupy all.
	Codes occupuy(Status attacker, int& outDate);

	// Get Land information from the console as appropriate.
	void setLandFromConsole();

private:
	int mWidth;
	int mHeight;

	Status** mBoard;
};

