#include "Land.h"

#include <iostream>
#include <iomanip>
#include <queue>

#include "string_jdh.h"

using namespace std;

Land::Land(int width, int height) {
	if (width < 0 || height < 0)
		throw invalid_argument("[!] Error. Land size must be positive.");

	mWidth = width;
	mHeight = height;

	// Create a two-dimensional Status array to fit the horizontal and vertical sizes.
	mBoard = new Status*[mHeight];
	for (int y = 0; y < mHeight; y++) {
		mBoard[y] = new Status[mWidth];
		for (int x = 0; x < mWidth; x++)
			mBoard[y][x] = NOT_INIT; // Then make it into NOT_INIT state.
	}

}

Land::~Land() {
	for (int y = 0; y < mHeight; y++)
		delete[] mBoard[y];
	delete[] mBoard;
}

void Land::setLandFromConsole() {

	int status;

	// Get Land information from the console as appropriate.
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			if (safeNumInput(cin, status, START + 1, END - 1, false)) {
				cout << "Status code must be in " << START + 1 << " ~ " << END - 1 << endl;
				throw logic_error("[!] Error. Invalid status code.");
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

	// Get the positions of attackers and the number of unoccupiable areas.
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

	// If the current queue is empty, return no soldiers.
	if (todayQueue.empty())
		return NO_SOLDIER;

	// Repeat until all occupiable areas are occupied.
	while (true) {
		cout << endl;
		 
		// If all occupiable areas are occupied.
		if (numberOfOccupied >= mWidth * mHeight - numberOfNone)
			return SUCCESS_OCCUPUY;

		// Repeat the following for the attacker currently in the queue.
		while (!todayQueue.empty()) {

			pair<int, int> currentPos = todayQueue.front();
			todayQueue.pop();

			// Repeat the following for the adjacent cell of the attacker.
			for (int dx = currentPos.first - 1 < 0 ? 0 : -1; dx <= (currentPos.first + 1 >= mWidth ? 0 : 1); dx++) {
				for (int dy = currentPos.second - 1 < 0 ? 0 : -1; dy <= (currentPos.second + 1 >= mHeight ? 0 : 1); dy++) {
				
					// If current cell isn't attacker itself and unoccupiable area.
					Status adjacentStatus = mBoard[currentPos.second + dy][currentPos.first + dx];
					if (adjacentStatus != attacker && adjacentStatus != NONE) {
						tomorrowQueue.push(make_pair(currentPos.first + dx, currentPos.second + dy));	// Put the information of the current cell into the next queue and
						mBoard[currentPos.second + dy][currentPos.first + dx] = attacker;				// occupy the current cell and
						numberOfOccupied++;																// increase the occupation number by 1.
					}
				}
			}
		}
		
		// If next queue is empty though occupiable area is exist.
		if (tomorrowQueue.empty())
			return SURROUNDED;

		// If you want to see the occupation status step by step, uncomment below.
		/*
		for (int y = 0; y < mHeight; y++) {
			for (int x = 0; x < mWidth; x++) {
				cout << setw(2) << mBoard[y][x] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		*/

		outDate++; // Increase the date by 1.

		// Makes the next queue the current queue.
		while (!tomorrowQueue.empty()) {
			todayQueue.push(tomorrowQueue.front());
			tomorrowQueue.pop();
		}
	}
}
