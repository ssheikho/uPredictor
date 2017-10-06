#include "FileIndex.h"

#include <cstdlib>

#ifdef _WIN32
	FileIndex::FileIndex(wstring fileName, long recsPerBlock
		, bool readExisting) : 
		_recsPerBlock(recsPerBlock), _nRecs(0) {
#elif __linux__
	FileIndex::FileIndex(string fileName, long recsPerBlock
		, bool readExisting) : 
		_recsPerBlock(recsPerBlock), _nRecs(0) {
#endif

	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
		pthread_mutex_lock(&_mutex);
	#endif

	if (readExisting) {
		_f.open(fileName.c_str(), ios::in | ios::binary);
		_f.read((char *)&_recsPerBlock, sizeof(long));
		_f.read((char *)&_nRecs, sizeof(long));

		std::streamoff off = _f.tellg();

		while (off > -1) {
			IndexBlock *ib = new IndexBlock(this, off, true);
			_indexBlocks.push_back(ib);

			off = ib->getNextBlockPos();
		}
	}
	else {
		_f.open(fileName.c_str(), ios::out | ios::trunc | ios::binary);
		_f.write((char *)&_recsPerBlock, sizeof(long));
		_f.write((char *)&_nRecs, sizeof(long));

		_indexBlocks.push_back(new IndexBlock(this, _f.tellp(), false));
	}

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

FileIndex::~FileIndex() {
	finalize();
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	for (int i = 0; i < _indexBlocks.size(); i++) delete _indexBlocks[i];
	_indexBlocks.clear();

	#ifdef _WIN32
		ReleaseMutex(_mutex);
		CloseHandle(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
		pthread_mutex_destroy(&_mutex);
	#endif
}

void FileIndex::write(unsigned char *data, long size) {
	IndexBlock *ib = _indexBlocks[_indexBlocks.size() - 1];
	ib->write(data, size);
}

long FileIndex::read(long index, unsigned char *data, long maxSize) {
	long indexInBlock = index % _recsPerBlock;
	long blockIndex = (index - indexInBlock) / _recsPerBlock;
	long size = _indexBlocks[blockIndex]->read(indexInBlock, data, maxSize);
	return size;
}

long FileIndex::getNRecs() {
	return _nRecs;
}

void FileIndex::finalize() {
	_f.seekp(0);
	_f.write((char *)&_recsPerBlock, sizeof(long));
	_f.write((char *)&_nRecs, sizeof(long));

	for (vector<IndexBlock *>::iterator iter = _indexBlocks.begin();
	iter != _indexBlocks.end(); iter++)
		(*iter)->finalize();
}

//_fi->_f.tellp()
FileIndex::IndexBlock::IndexBlock(FileIndex *fi, std::streamoff blockPos,
	bool loadFromFile) :
	_fi(fi)
	, _nRecs(0)
	, _blockPos(blockPos)
	, _nextBlockPos(-1)
	, _index(new std::streamoff[_fi->_recsPerBlock]) {

	if (loadFromFile) {
		readMetadata();
	}
	else {
		finalize();
		_index[_nRecs] = _fi->_f.tellp();
	}
}

FileIndex::IndexBlock::~IndexBlock() {
	finalize();
	delete[] _index;
}

void FileIndex::IndexBlock::setNextBlockPos(std::streamoff nextBlockPos) {
	_nextBlockPos = nextBlockPos;
}

bool FileIndex::IndexBlock::hasMoreSpace() {
	return _nRecs < _fi->_recsPerBlock;
}

void FileIndex::IndexBlock::write(unsigned char *data, long size) {
	_fi->_f.seekp(_index[_nRecs]);

	_fi->_f.write((char *)&size, sizeof(long));
	_fi->_f.write((char *)data, size);

	_nRecs++;
	_fi->_nRecs++;

	if (_nRecs == _fi->_recsPerBlock) {
		_nextBlockPos = _fi->_f.tellp();
		_fi->_indexBlocks.push_back(new IndexBlock(_fi, _nextBlockPos,
			false));
	}
	else {
		_index[_nRecs] = _fi->_f.tellp();
	}
}

long FileIndex::IndexBlock::read(long indexInBlock, unsigned char *data,
	long maxSize) {
	long size;
	_fi->_f.seekg(_index[indexInBlock]);
	_fi->_f.read((char *)&size, sizeof(long));
	if (size > maxSize) abort();
	_fi->_f.read((char *)data, size);

	return size;
}

void FileIndex::IndexBlock::readMetadata() {
	size_t ptSize = sizeof(std::streamoff);
	_fi->_f.seekg(_blockPos);
	_fi->_f.read((char *)&_nextBlockPos, ptSize);
	_fi->_f.read((char *)&_nRecs, sizeof(long));
	_fi->_f.read((char *)_index, _fi->_recsPerBlock * sizeof(std::streamoff));
}

void FileIndex::IndexBlock::finalize() {
	size_t ptSize = sizeof(std::streamoff);
	_fi->_f.seekp(_blockPos);
	_fi->_f.write((char *)&_nextBlockPos, ptSize);
	_fi->_f.write((char *)&_nRecs, sizeof(long));
	_fi->_f.write((char *)_index, _fi->_recsPerBlock * sizeof(std::streamoff));
}

std::streamoff FileIndex::IndexBlock::getBlockPos() {
	return _blockPos;
}

std::streamoff FileIndex::IndexBlock::getNextBlockPos() {
	return _nextBlockPos;
}
