#pragma once

#include "Node.h"

class CategoryNode : public Node {
private:
	char	mName[64];

public:
	CategoryNode(const char name[]) { strcpy(mName, name); }

	bool isMe(string name) const { return string(mName) == name; }
	const char* getName() const { return mName; }
	string getType() const override { return "category"; }
};