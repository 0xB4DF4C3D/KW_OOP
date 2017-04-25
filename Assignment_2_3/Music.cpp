#include "Music.h"

#include <iostream>

#include "myString.h"

using namespace std;

Music::Music() {

	// Initiallize basic member variables.
	mRank = 0;
	my_cpy(mTitle, "");
	my_cpy(mSinger, "");
	mReleaseYear = 0;
}


Music::~Music() {

	// Make the rank DELETED_ENTRY and exclude it from the music list.
	mRank = Music::DELETED_ENTRY;
}

int Music::getRank() const {
	return mRank;
}

void Music::setRank(int rank) {
	if (rank < 0 || rank > Music::RANK_MAX) {
		cerr << "rank must be in " << 0 << " ~ " << Music::RANK_MAX << endl;
		throw invalid_argument("[!] Error. rank is invalid argument.");
	}

	mRank = rank;
}

const char* Music::getTitle() const {
	return mTitle;
}

void Music::setTitle(char* title) {
	if (my_len(title) >= TITLE_SIZE || my_len(title) == 0) {
		cerr << "title length must be in " << 1 << " ~ " << TITLE_SIZE << endl;
		throw invalid_argument("[!] Error. title is invalid argument.");
	}

	my_cpy(mTitle, title);
}

const char* Music::getSinger() const {
	return mSinger;
}

void Music::setSinger(char* singer) {
	if (my_len(singer) >= SINGER_SIZE || my_len(singer) == 0) {
		cerr << "singer length must be in " << 1 << " ~ " << SINGER_SIZE << endl;
		throw invalid_argument("[!] Error. singer is invalid argument");
	}

	my_cpy(mSinger, singer);
}

int Music::getReleaseYear() const {
	return mReleaseYear;
}

void Music::setReleaseYear(int releaseYear) {
	if (releaseYear < 0 || releaseYear > YEAR_MAX) {
		cerr << "releaseYear must be in " << 0 << " ~ " << YEAR_MAX << endl;
		throw invalid_argument("[!] Error. releaseYear is invalid argument");
	}

	mReleaseYear = releaseYear;
}

void swap(Music& a, Music& b) {
	Music temp = a;
	a = b;
	b = temp;
}
