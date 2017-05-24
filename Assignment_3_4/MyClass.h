#pragma once

#include <iostream>

class MyClass {
private:
	int m_num;

public:
	MyClass() : m_num(0) {};
	void PrintNum(const char* name)
	{
		std::cout
			<< name << ": " << m_num++
			<< std::endl;
	}
};

