#pragma once

class Music {
public:
	
	// Constants related to music.
	static const size_t YEAR_MAX = 9999;
	static const size_t RANK_MAX = 99999;
	static const size_t TITLE_SIZE = 128;
	static const size_t SINGER_SIZE = 128;

	static const int DELETED_ENTRY = -1;

	enum PROP {
		RANK = 1, TITLE, SINGER, RELEASE_YEAR
	};

	Music();
	~Music();

	// Getters and setters.
	int getRank() const;
	void setRank(int rank);

	const char* getTitle() const;
	void setTitle(char* title);

	const char* getSinger() const;
	void setSinger(char* singer);

	int getReleaseYear() const;
	void setReleaseYear(int releaseYear);
	
private:
	int mRank;
	char mTitle[Music::TITLE_SIZE];
	char mSinger[Music::SINGER_SIZE];
	int mReleaseYear;
};

// Custom swap function for sorting.
void swap(Music& a, Music& b);
