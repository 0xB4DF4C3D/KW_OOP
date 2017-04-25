#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class RandomNumberSorter {
private:
	int randomCount; // The number of random values to select.

	// Structure that maintains an existing index value.
	struct Rank {
		unsigned int index;
		unsigned int count;
	};
	const int RANK_MAX;	// Maximum random value constant.
	Rank *randomList;	// List of values to handle.

	void sortRank(Rank* numberList);	// Sort the given numberList.

public:
	RandomNumberSorter(int rank_max) :RANK_MAX(rank_max) {
		randomList = new Rank[RANK_MAX];
	};
	~RandomNumberSorter() { delete[] randomList; };

	bool setCount();			// Receives the numberCount value from console.
	void calculate();				// Randomly pick and sort.
	void print();					// Output the result.

};

template<typename T1> // Templates for various streams.
bool safeIntInput(T1 &stream, int& i, int min, int max, bool onlyGetOne) {
	stream >> i;
	if (cin.fail() || i < min || i > max) { // Invalid input or out of range.
		cerr << "[!] Input must be in " << min << "~" << max << endl;
		stream.clear(); stream.ignore(INT_MAX, '\n'); // Initialize the stream.
		return EXIT_FAILURE;
	}
	if (onlyGetOne) { // If the onlyGetOne flag is on
		char c;
		while (stream.get(c) && c != '\n') { // Check for additional input after.
			if (!isspace(c)) {
				cerr << "[!] There are strange values behind." << endl;
				stream.clear(); stream.ignore(INT_MAX, '\n'); // Initialize the stream.
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

int main() {

	int randomNumber;
	RandomNumberSorter rns(20);

	do {
		if (!rns.setCount())	// 1. Input number of random values to pick.
			break;
	} while (true);

	rns.calculate();		// 2. Calculate and keep it.
	rns.print();			// 3. Output the result.
	return EXIT_SUCCESS;
}



void RandomNumberSorter::sortRank(Rank* numberList) {
	// Implemented as bubble sort with Rank struct.

	Rank tempElement;

	for (int i = 1; i < RANK_MAX; i++) {
		for (int j = 0; j < RANK_MAX - i; j++) {
			if (numberList[j].count < numberList[j + 1].count) {
				tempElement = numberList[j];
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = tempElement;
			}
		}
	}
}


bool RandomNumberSorter::setCount() {
	// interface that accepts only the appropriate values.
	cout << "Input N: ";

	return safeIntInput(cin, randomCount, 1, INT_MAX, true);
}


void RandomNumberSorter::print() {
	// Traverse randomList.
	for (int i = 0; i < RANK_MAX; i++)
		if (randomList[i].count == 0)	// If count is 0, then ignore. 
			continue;
		else							// If count isn't 0, then print.
			cout << randomList[i].index << " - " << randomList[i].count << endl;

	cout << endl;
}


void RandomNumberSorter::calculate() {
	// Randomly pick and sort.

	int randomNumber;
	srand((unsigned)time(NULL)); // Initialize the seed value.

	// Initialize randomList.
	for (unsigned int i = 0; i < RANK_MAX; i++) {
		randomList[i].index = RANK_MAX - i; // For the bigger random number comes first.
		randomList[i].count = 0;
	}

	cout << "Random number: ";
	for (int i = 0; i < randomCount; i++) {

		// Randomly pick one and increment the value of that index by 1.
		randomNumber = (unsigned int)rand() % RANK_MAX;
		randomList[randomNumber].count++;

		cout << randomNumber << ' ';
	}
	cout << endl;

	// Sort by count.
	sortRank(randomList);
}