#include "string_jdh.h"

#include <cstdlib>
#include <ctype.h>

// Calculate the length of the string.
int my_len(char* str1) {
	int stringLength;

	for (stringLength = 0; str1[stringLength] != NULL; stringLength++);

	return stringLength;
}

// Copy str1 string value to str2.
char* my_cpy(char* str2, char* str1) {

	char* str2Ptr = str2, *str1Ptr = str1;
	while (*str1Ptr != NULL)
		*str2Ptr++ = *str1Ptr++;
	*str2Ptr = NULL;
	return str2;
}

// Tokenize str1 as delimiters.
char* my_tok(char* str1, char* delimiters) {

	static char* currentCharacter; // the character to be processed

	if (str1 == NULL) {
		if (*currentCharacter == NULL) {// If str1 is NULL and currentCharacter is also NULL, all strings are tokenized.
			return NULL;				// So do nothing and return NULL.
		} else {
			str1 = currentCharacter;	// If str1 is NULL and currentCharacter is not NULL, 
										// it means that there are strings left to process.
		}
	} else {							// If str1 is not NULL, 
		currentCharacter = str1;		// it means that the string to be processed is new.
	}

	char* currentDelimiter;
	// Repeats while currentCharacter is not NULL.
	while (*currentCharacter != NULL) {
		currentDelimiter = delimiters;

		// Repeats while the delimiter is not NULL.
		while (*currentDelimiter != NULL) {

			// If one of the characters in the delimiter matches currentCharacter
			if (*currentCharacter == *currentDelimiter) {
				*currentCharacter = NULL;	// Make currentCharacter NULL, 
				currentCharacter++;			// make it point to the next character, 
				return str1;				// and then return str1 that tokenized till current.
			}
			currentDelimiter++;
		}
		currentCharacter++;
	}

	return str1;
}

// Compare str1 and str2.
int my_cmp(const char* str1, const char* str2) {

	// Declaring pointers to given strings.
	const char* currentStr1 = str1, *currentStr2 = str2;

	do { // Returns 1 if the string in str1 is greater in alphabetical order,
		 // or -1 if it is less.
		if (*currentStr1 > *currentStr2)
			return 1;
		else if (*currentStr1 < *currentStr2)
			return -1;
		currentStr1++; currentStr2++;
	} while ((*currentStr1 || *currentStr2));

	return 0;
}

// Verify that the given C style string is only a number.
bool validateNumeric(const char* numericString) {
	const char* ptr = numericString;
	bool symbolFlag = false;

	if (*ptr == '-') // Pass for minus signed number.
		ptr++;

	// Check for all characters in a given string using the isdigit function.
	// And allows points for decimal points.
	while (*ptr != NULL) {
		if (*ptr == '.') {
			if (symbolFlag)		// If the decimal point appears twice, 
				return false;	// it returns a decimal conversion failure.
			else
				symbolFlag = true;
		} else if (!isdigit(*ptr))	// Or if it is not just a number 
			return false;			// then it will return a numeric conversion failure.
		ptr++;
	}

	// Returns true if it consists only of digits until the end.
	return true;
}