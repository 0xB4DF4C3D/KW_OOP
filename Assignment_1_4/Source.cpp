#include <iostream>
#include <cmath>

using namespace std;

inline bool isAlpha(const char& c) {
	// Check whether the given character is alphabetic.
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool CompareString(const char *str1, const char *str2) {

	// Ptr1 and ptr2 point to the beginning of each string pointer.
	const char *ptr1 = str1;
	const char *ptr2 = str2;

	// Both ptr1 and ptr2 loop continuously while 
	// they are not yet at the end of the string.
	while (*ptr1 && *ptr2) {

		// If the characters to be compared at present are both alphabets.
		if ( isAlpha(*ptr1) && isAlpha(*ptr2)) {

			// Then they are not case sensitive.
			if (*ptr1 != *ptr2 && (abs(*ptr1 - *ptr2) != 'a' - 'A'))
				return false;
		}
		else if(*ptr1 != *ptr2)
			return false;
		
		// Point to the next letter.
		ptr1++;
		ptr2++;
	}

	// If both strings have the same length, they will be true as NULL,
	// otherwise they will not be equal.
	return *ptr1 == *ptr2;
}

int main() {
	char str1[64], str2[64];
	
	cout << "str1: ";
	cin.getline(str1, 64, '\n');
	
	cout << "str2: ";
	cin.getline(str2, 64, '\n');
	
	if (CompareString(str1, str2)) 
		cout << "They are equal." << endl;
	else 
		cout << "They are different." << endl;
	
	return EXIT_SUCCESS;
}