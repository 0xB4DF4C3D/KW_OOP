#include "StringManipulator.h"


using namespace std;

StringManipulator::StringManipulator() {
}


StringManipulator::~StringManipulator() {
}


int StringManipulator::my_len(char* str1) {
	int stringLength;
	for (stringLength = 0; str1[stringLength] != '\x00'; stringLength++);
	return stringLength;
}


char* StringManipulator::my_cpy(char* str2, char* str1) {
	int originalLength = my_len(str1);
	int i;

	for (i = 0; i <= originalLength; i++)
		str2[i] = str1[i];

	return str2;
}


char* StringManipulator::my_tok(char* str1, char* delimiters) {
	return nullptr;
}
