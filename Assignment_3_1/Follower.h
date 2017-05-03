#pragma once
class Follower {
public:
	Follower();
	~Follower();

	char* getWord() const;
	void setWord(const char*);

	int getCount() const;
	void setCount(int count);

	Follower* getNext() const;
	void setNext(Follower* next);

private:
	char* mWord;
	int mCount;
	Follower* mNext;

};

