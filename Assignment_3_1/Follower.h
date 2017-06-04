#pragma once
class Follower {
public:
	Follower();
	Follower(const char* word);

	~Follower();

	char* getWord() const;
	void setWord(const char*);

	int getCount() const;
	void setCount(int count);

	Follower* getNext() const;
	void setNext(Follower* next);

private:
	char* mWord;
	int mCount; // Follower has Count instead of Size, unlike Item.
	Follower* mNext;

};

