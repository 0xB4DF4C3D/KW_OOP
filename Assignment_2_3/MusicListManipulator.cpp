#include "MusicListManipulator.h"

#include <iomanip>

#include "myString.h"

using namespace std;

// This function is only used in MusicListManipulator this file, and it opens the file safely.
void validFileOpen(fstream& stream, const char* fileName, int mode = 3) {
	stream.open(fileName, mode);

	// If it fails to open ...
	if (stream.fail()) {
		cerr << "Failed to open " << fileName << '.' << endl;
		cerr << "Program will be aborted." << endl;
		exit(EXIT_FAILURE); 
	};
}


MusicListManipulator::MusicListManipulator(char* fileName) {
	// Save the file name in a member variable called mFileName 
	// because it will continue to used it later.
	my_cpy(mFileName, fileName);
	loadMusicList();
}


MusicListManipulator::~MusicListManipulator() {
	delete[] mMusicList;
}


void MusicListManipulator::updateMusic(int originRank, int newRank, char* title, char* singer, unsigned int releaseYear) {

	int originIdx = 0;

	// Look for Music with the rank corresponding to originRank.
	for (unsigned int idx = 0; idx < mEntryCount; idx++) {
		if (mMusicList[idx].getRank() == originRank) {
			originIdx = idx;
			break;
		}
	}

	// Update the information of found music.
	mMusicList[originIdx].setRank(newRank);
	mMusicList[originIdx].setTitle(title);
	mMusicList[originIdx].setSinger(singer);
	mMusicList[originIdx].setReleaseYear(releaseYear);

	updateFile(); // Update the file too.
}

void MusicListManipulator::updateFile() {
	// Note that this process creates and deletes, no overwrites and appends.
	validFileOpen(mFile, mFileName, ios::out | ios::trunc);

	// Update the file with the current MusicList information.
	// If the Rank value is DELETED_ENTRY in this process, it is not saved.
	unsigned int idx;
	for (idx = 0; idx < mEntryCount - 1; idx++)
		if (mMusicList[idx].getRank() != Music::DELETED_ENTRY)
			mFile << mMusicList[idx].getRank() << '/'
			<< mMusicList[idx].getTitle() << '/'
			<< mMusicList[idx].getSinger() << '/'
			<< mMusicList[idx].getReleaseYear() << endl;

	if (mMusicList[idx].getRank() != Music::DELETED_ENTRY)
		mFile << mMusicList[idx].getRank() << '/'
		<< mMusicList[idx].getTitle() << '/'
		<< mMusicList[idx].getSinger() << '/'
		<< mMusicList[idx].getReleaseYear(); // This is to ignore the last empty line.

	mFile.close();
}



void MusicListManipulator::insertMusic(int rank, char* song, char* singerName, unsigned int year) {
	// Adds a new Music to the end of the file and reloads it to update both the MusicList and the file.
	
	validFileOpen(mFile, mFileName, ios::app);

	mFile << '\n' << rank << '/' << song << '/' << singerName << '/' << year;
	mFile.close();

	loadMusicList();
}

void MusicListManipulator::loadMusicList() {
	validFileOpen(mFile, mFileName);

	char *token;
	char lineBuf[BUFSIZ];

	// Gets the number of entries stored in the file.
	mEntryCount = 0;
	while (mFile.getline(lineBuf, BUFSIZ))
		mEntryCount++;
	mFile.clear();
	mFile.seekg(0);

	// Deletes an existing MusicList.
	mMusicList = nullptr;
	delete[] mMusicList;

	mMusicList = new Music[mEntryCount];

	// If the file structure is inappropriate for the following reasons:
	//		If the letter comes where the numbers should come.
	//		The range of values is too small or too large.
	// If so, the program will be aborted.
	try {
		// Each line is searched and the data is read.
		for (int idx = 0; idx < mEntryCount; idx++) {
			mFile.getline(lineBuf, BUFSIZ);

			token = my_tok(lineBuf, "/");
			if (!validateNumeric(token))
				throw exception("[!] Error. Rank must be a number.");
			mMusicList[idx].setRank(atoi(token));

			token = my_tok(NULL, "/");
			mMusicList[idx].setTitle(token);

			token = my_tok(NULL, "/");
			mMusicList[idx].setSinger(token);

			token = my_tok(NULL, "/");
			if (!validateNumeric(token))
				throw exception("[!] Error. Rank must be a number.");
			mMusicList[idx].setReleaseYear(atoi(token));
		}
	} catch (const exception& e) {
		cerr << e.what() << endl;
		cerr << "Program will be aborted." << endl;
		mFile.close();
		exit(EXIT_FAILURE);
	}

	// outputs the current MusicList information each time it load.
	for (int idx = 0; idx < mEntryCount; idx++) {
		cout << '[' << setw(5) << mMusicList[idx].getRank() << "]\t"
			<< mMusicList[idx].getTitle() << "( "
			<< mMusicList[idx].getSinger() << " )\t" << mMusicList[idx].getReleaseYear() << endl;
	}
	cout << endl;

	mFile.close();
}

void MusicListManipulator::sortMusic(int sortType) {

	// Sort MusicList using bubble sort according to given sortType.
	// This implementation increases the code but reduces the number of branches that need to be handled.
	switch (sortType) {
	case RANK:
		for (int i = 0; i < mEntryCount - 1; i++)
			for (int j = mEntryCount - 1; j > i; j--)
				if (mMusicList[j].getRank() > mMusicList[j - 1].getRank())
					swap(mMusicList[j], mMusicList[j - 1]);
		break;

	case SONG_NAME:
		for (int i = 0; i < mEntryCount - 1; i++)
			for (int j = mEntryCount - 1; j > i; j--)
				if (my_cmp(mMusicList[j].getTitle(), mMusicList[j - 1].getTitle()) > 0)
					swap(mMusicList[j], mMusicList[j - 1]);
		break;

	case SINGER_NAME:
		for (int i = 0; i < mEntryCount - 1; i++)
			for (int j = mEntryCount - 1; j > i; j--)
				if (my_cmp(mMusicList[j].getSinger(), mMusicList[j - 1].getSinger()) > 0)
					swap(mMusicList[j], mMusicList[j - 1]);
		break;

	case RELEASE_YEAR:
		for (int i = 0; i < mEntryCount - 1; i++)
			for (int j = mEntryCount - 1; j > i; j--)
				if (mMusicList[j].getReleaseYear() > mMusicList[j - 1].getReleaseYear())
					swap(mMusicList[j], mMusicList[j - 1]);
		break;
	}

	// Then save it to a file and reload it.
	updateFile();
	loadMusicList();
}

bool MusicListManipulator::checkExistMusic(int rank) {
	
	// traverses all musicList and finds the music corresponding to the given rank.
	for (int idx = 0; idx < mEntryCount; idx++) {
		if (mMusicList[idx].getRank() == rank)
			return true; // Return true if found.
	}

	return false; // If not found, return false.
}



void MusicListManipulator::deleteMusic(int rank) {
	int deletedIdx = 0;

	// Find music which has rank corresponed to a rank to be deleted.
	for (int idx = 0; idx < mEntryCount; idx++) {
		if (mMusicList[idx].getRank() == rank) {
			deletedIdx = idx;
			break;
		}
	}

	// Invoke destructor for that Music.
	mMusicList[deletedIdx].~Music();
	// As a result, the rank of the corresponding music becomes the DELETED_ENTRY value, 
	// and this value can not be set from the outside except the destructor.

	// Then save it to a file and reload it.
	updateFile();
	loadMusicList();
}
