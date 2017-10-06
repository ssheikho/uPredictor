#ifndef FILE_INDEX_H
#define FILE_INDEX_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include <fstream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
Error codes:
-1 - No block at index
-2 - No record at index (block exists)

*/

class FileIndex {
public:
	#ifdef _WIN32
		FileIndex(wstring fileName, long recsPerBlock, bool readExisting);
	#elif __linux__
		FileIndex(string fileName, long recsPerBlock, bool readExisting);
	#endif

	~FileIndex();

	void write(unsigned char *data, long size);
	long read(long index, unsigned char *data, long maxSize);
	long getNRecs();
	void finalize();
	
protected:
	class IndexBlock {
	public:
		IndexBlock(FileIndex *fi, std::streamoff blockPos, bool loadFromFile);
		~IndexBlock();

		void setNextBlockPos(std::streamoff nextBlockPos);
		bool hasMoreSpace();
		void write(unsigned char *data, long size);
		long read(long indexInBlock, unsigned char *data, long maxSize);

		void readMetadata();
		void finalize();

		std::streamoff getBlockPos();
		std::streamoff getNextBlockPos();

	protected:
		FileIndex *_fi;
		long _nRecs;
		std::streamoff _blockPos, _nextBlockPos, *_index;
	};
	
	fstream _f;
	long _recsPerBlock, _nRecs;
	vector<IndexBlock *> _indexBlocks;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif
};

#endif
