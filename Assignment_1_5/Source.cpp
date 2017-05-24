#include <iostream>
#include <fstream>

using namespace std;

class LargestSummer {
public:
	LargestSummer() {};
	~LargestSummer() {

		// Deletes dynamic arrays.
		// Construction & destruction pairs may not be correct.
		// So I initialized the pointer to nullptr.
		delete[] totalArray;
		delete[] subArrayLeft;
		delete[] subArrayRight;
	};

protected:

	// Returns a computed decimal number with an array of index weights.
	int arrayToDecimal(const int numberArray[], int arraySize);
	void sort(int numberArray[], int arraySize);

private:
	ifstream inputStream;

	// Declare an array to hold all numbers and an array to split into two.
	int *totalArray = nullptr, *subArrayLeft = nullptr, *subArrayRight = nullptr;
	int totalArrSize, subArrSize;

public:
	bool readFile(const char fileName[]);	// Reads the file from fileName.
	bool printResult();						// The result is calculated and output.
};

template<typename T1> // Templates for various streams.
bool safeIntInput(T1 &stream, int& i, int min, int max, bool onlyGetOne = true) {
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

	LargestSummer largestSummer;

	try {
		largestSummer.readFile("input.txt");
		largestSummer.printResult();
	} catch (const exception& e) {
		cerr << e.what() << endl;
		cerr << "[!] Something is wrong. Program exit." << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void LargestSummer::sort(int numberArray[], int arraySize) {
	// Implemented as bubble sort with Rank struct.

	int tempElement;

	for (int i = 1; i < arraySize; i++) {
		for (int j = 0; j < arraySize - i; j++) {
			if (numberArray[j] < numberArray[j + 1]) {
				tempElement = numberArray[j];
				numberArray[j] = numberArray[j + 1];
				numberArray[j + 1] = tempElement;
			}
		}
	}
}

int LargestSummer::arrayToDecimal(const int numberArray[], int arraySize) {
	// Returns a computed decimal number with an array of index weights.

	int result = 0;
	int idx = 0;

	// Combine the numbers in numberArray into a single decimal number.
	while (idx < arraySize)
		result = result * 10 + numberArray[idx++];

	return result;
}

bool LargestSummer::readFile(const char fileName[]) {

	inputStream.open(fileName);
	if (inputStream.fail()) // Make sure the file is opened correctly.
		throw ifstream::failure("[!] Error. Can't open file\n");

	// Check whether the total number range is appropriate and even.
	if (safeIntInput(inputStream, totalArrSize, 0, 20, true)) {
		inputStream.close();
		throw out_of_range("[!] Error. Out of range in totalArrSize.\n");
	}
	if (totalArrSize % 2 == 1) {
		inputStream.close();
		throw logic_error("[!] Error. Input must be even.\n");
	}

	// Dynamic array allocation for operations.
	totalArray = new int[totalArrSize];
	subArrayLeft = new int[totalArrSize / 2];
	subArrayRight = new int[totalArrSize / 2];

	// Variables to receive numeric input from a file.
	int idx = 0;
	int input;

	do {
		// If the current number of inputs exceeds totalArrSize.
		if (idx >= totalArrSize) {
			inputStream.close(); // Closes the file and throws an error.
			throw length_error("[!] Error. Too many input.\n");
		}

		// Get a number from inputStream and check the range.
		if (safeIntInput(inputStream, input, 0, 9, false)) {
			inputStream.close(); // Closes the file and throws an error.
			throw out_of_range("[!] Error. Out of range in input.\n");
		} // Also check for strange characters, not numbers.
		else if (!inputStream.eof() && (int)inputStream.tellg() == -1) {
			inputStream.close(); // Closes the file and throws an error.
			throw out_of_range("[!] Error. Strange characters, not numbers.\n");
		} else // If there is no problem, put the current number in totalArray.
			totalArray[idx++] = input;
	} // It continues to read the file unitl it is at the end of the file or linebreak. 
	while (!inputStream.eof() && inputStream.peek() != '\n');

	if (idx < totalArrSize) { // If the number of input read is less than totalArrSize.
		inputStream.close(); // Closes the file and throws an error.
		throw length_error("[!] Error. Too less input.\n");
	}

	inputStream.close();
	return EXIT_SUCCESS;

}

bool LargestSummer::printResult() {
	sort(totalArray, totalArrSize);	// Sort the entire array.
	subArrSize = totalArrSize / 2;	// Defines the size of the subArray.

	// Among the numbers which have not selected yet, 
	// choose the largest and the smallest alternately.
	for (int i = 0; i < subArrSize; i++)
		subArrayLeft[i] = (i % 2 ? totalArray[totalArrSize - ((i + 1) / 2)] : totalArray[i / 2]);
	// Then put it in the left subArray and sort it.
	sort(subArrayLeft, subArrSize);

	// Among the numbers which have not selected yet, 
	// choose the largest and the smallest alternately.
	for (int i = subArrSize; i < totalArrSize; i++)
		subArrayRight[i - (subArrSize)] = (i % 2 ? totalArray[totalArrSize - ((i + 1) / 2)] : totalArray[i / 2]);
	// Then put it in the right subArray and sort it.
	sort(subArrayRight, subArrSize);

	// Pass the values contained in the subArray to arrayToDecimal 
	// and return numbers.
	int subValueLeft, subValueRight;
	subValueLeft = arrayToDecimal(subArrayLeft, subArrSize);
	subValueRight = arrayToDecimal(subArrayRight, subArrSize);

	// Outputs both the values and sum.
	cout << subValueLeft << " + " << subValueRight << " = " << subValueLeft + subValueRight << endl;
	return EXIT_SUCCESS;
}

