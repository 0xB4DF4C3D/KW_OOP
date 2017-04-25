#pragma once

#include <iostream>

class StringManipulator {
public:
	StringManipulator();
	~StringManipulator();
	int my_len(char* str1);
	char* my_cpy(char* str2, char* str1);
	char* my_tok(char* str1, char* delimiters);
};

