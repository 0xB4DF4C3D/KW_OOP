#include "Days.h"

#include <iostream>

using namespace CDays;
using namespace std;

Wed::Wed() {
}

Wed::~Wed() {
}

void Wed::PrintTitle(int num) {
	if (num == 1)
		cout << "** Score List of Wednesday sorted by Name **" << endl;
	else
		cout << "** Score List of Wednesday sorted by Score **" << endl;
}


Thu::Thu() {
}

Thu::~Thu() {
}

void Thu::PrintTitle(int num) {
	if (num == 1)
		cout << "** Score List of Thursday sorted by Name **" << endl;
	else
		cout << "** Score List of Thursday sorted by Score **" << endl;
}


Fri::Fri() {
}

Fri::~Fri() {
}

void Fri::PrintTitle(int num) {
	if (num == 1)
		cout << "** Score List of Friday sorted by Name **" << endl;
	else
		cout << "** Score List of Friday sorted by Score **" << endl;
}


None::None() {
}

None::~None() {
}

void None::PrintTitle(int num) {
	if (num == 1)
		cout << "** Score List of None day sorted by Name **" << endl;
	else
		cout << "** Score List of None day sorted by Score **" << endl;
}
