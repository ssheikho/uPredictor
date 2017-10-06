#ifndef BLOB_PT_SET_H
#define BLOB_PT_SET_H

#include <map>
#include <queue>

//using namespace std;

class BlobPts;

class BlobPtSet {
public:
	BlobPtSet(int maxPtsPerBlob);
	~BlobPtSet();

	BlobPts *getClean();
	BlobPts *getByID(int id);
	void returnToPool(BlobPts *bp);
	void reset();

protected:
	int _maxPtsPerBlob, _curId;
	std::map<int, BlobPts *> _bp;
	std::queue<BlobPts *> _clean;
};

#endif