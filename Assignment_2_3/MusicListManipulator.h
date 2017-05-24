#pragma once

#include <fstream>
#include <iostream>

#include "Music.h"

// A class that manages and manipulates MusicList.
class MusicListManipulator {
public:
	MusicListManipulator(char *fileName); // It takes fileName and opens it in the mFile stream.
	~MusicListManipulator();

	// Provides basic CRUD operation and sorting.
	void insertMusic(int rank, char* title, char* singer, unsigned int releaseYear);
	void updateMusic(int originRank, int rank, char* title, char* singer, unsigned int releaseYear);
	void deleteMusic(int rank);
	void sortMusic(Music::PROP sortType);

	// Public Rank check function for menu interface.
	bool checkExistMusic(int rank);
private:

	Music *mMusicList = nullptr;

	std::fstream mFile;
	char mFileName[BUFSIZ];
	int mEntryCount = 0;

	void updateFile();		// Update the file with information from the current Music List and the File Name member variable.
	void loadMusicList();	// The information is retrieved from the file via the FileName member variable.
};

