#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

class Node
{
private:
	Node*	pNext;
	Node*	pDown;
	Node*	pUp;

public:
	Node() {
		pNext = NULL;
		pDown = NULL;
		pUp = NULL;
	};
	~Node() {};

	Node* getNext() { return pNext; }	
	Node* getUp()	{ return pUp; }
	Node* getDown() { return pDown; }
	virtual const char* getName() const = 0;

	virtual bool isMe(string name) const = 0;

	void setNext(Node* pN)	{ pNext = pN; }
	void setUp(Node* pN)	{ pUp = pN; }
	void setDown(Node* pN)	{ pDown = pN; }
};