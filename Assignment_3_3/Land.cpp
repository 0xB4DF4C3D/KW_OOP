#include "Land.h"

#include <iostream>
#include <iomanip>
#include <queue>

#include "string_jdh.h"

using namespace std;

Land::Land(int width, int height) {
	if (width < 0 || height < 0)
		throw invalid_argument(" error. ");

	mWidth = width;
	mHeight = height;

	mBoard = new Status*[mHeight];
	for (int y = 0; y < mHeight; y++) {
		mBoard[y] = new Status[mWidth];
		for (int x = 0; x < mWidth; x++)
			mBoard[y][x] = NOT_INIT;
	}
}

Land::~Land() {
	for (int y = 0; y < mHeight; y++)
		delete[] mBoard[y];
	delete[] mBoard;
}

void Land::setLandFromConsole() {

	int status;

	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			if (safeNumInput(cin, status, START + 1, END - 1, false)) {
				throw invalid_argument(" error. ");
			} else {
				mBoard[y][x] = static_cast<Status>(status);
			}
		}
	}
}

Land::Codes Land::occupuy(Status attacker, int& outDate) {

	int numberOfNone = 0, numberOfOccupied = 0;
	outDate = 0;
	queue<pair<int, int>> todayQueue, tomorrowQueue;

	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			if (mBoard[y][x] == attacker) {
				todayQueue.push(make_pair(x, y));
				numberOfOccupied++;
			}

			if (mBoard[y][x] == NONE)
				numberOfNone++;
		}
	}

	if (todayQueue.empty())
		return NO_SOLDIER;

	while (true) {
		cout << endl;

		if (numberOfOccupied >= mWidth * mHeight - numberOfNone)
			return SUCCESS_OCCUPUY;

		while (!todayQueue.empty()) {

			pair<int, int> currentPos = todayQueue.front();
			todayQueue.pop();
			for (int dx = currentPos.first - 1 < 0 ? 0 : -1; dx <= (currentPos.first + 1 >= mWidth ? 0 : 1); dx++) {
				for (int dy = currentPos.second - 1 < 0 ? 0 : -1; dy <= (currentPos.second + 1 >= mHeight ? 0 : 1); dy++) {
					Status adjacentStatus = mBoard[currentPos.second + dy][currentPos.first + dx];
					if (adjacentStatus != attacker && adjacentStatus != NONE) {
						tomorrowQueue.push(make_pair(currentPos.first + dx, currentPos.second + dy));
						mBoard[currentPos.second + dy][currentPos.first + dx] = attacker;
						numberOfOccupied++;
					}
				}
			}
		}

		if (tomorrowQueue.empty())
			return SURROUNDED;

		for (int y = 0; y < mHeight; y++) {
			for (int x = 0; x < mWidth; x++) {
				cout << setw(2) << mBoard[y][x] << ' ';
			}
			cout << endl;
		}
		cout << endl;

		outDate++;

		while (!tomorrowQueue.empty()) {
			todayQueue.push(tomorrowQueue.front());
			tomorrowQueue.pop();
		}
	}
}
