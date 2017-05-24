#pragma once

class Land {
public:

	enum Status {
		START = -2, NONE, JAPAN, KOREAN, END, NOT_INIT = 99
	};

	enum Codes {
		NO_SOLDIER, SURROUNDED, NO_LAND_TO_OCCUPUY, SUCCESS_OCCUPUY
	};

	Land(int width, int height);
	~Land();

	void setLandFromConsole();

	Codes occupuy(Status attacker, int& outDate);

private:
	int mWidth;
	int mHeight;

	Status** mBoard;
};

