#include "BlobPtSet.h"
#include "BlobPts.h"

BlobPtSet::BlobPtSet(int maxPtsPerBlob) :
	_maxPtsPerBlob(maxPtsPerBlob)
	, _curId(1)
{}

BlobPtSet::~BlobPtSet() {}

BlobPts *BlobPtSet::getClean() {
	BlobPts *retVal = NULL;

	if (_clean.size()) {
		retVal = _clean.front();
		_clean.pop();
	}
	else {
		retVal = new BlobPts(_maxPtsPerBlob, _curId);
		_curId++;
	}

	_bp[retVal->getID()] = retVal;

	return retVal;
}

BlobPts *BlobPtSet::getByID(int id) {
	BlobPts *retVal = NULL;
	if (id != 0) {
		map<int, BlobPts *>::iterator iter = _bp.find(id);
		if (iter != _bp.end()) retVal = iter->second;
	}
	return retVal;
}

void BlobPtSet::returnToPool(BlobPts *bp) {
	bp->reset();
	_bp.erase(_bp.find(bp->getID()));
	_clean.push(bp);
}

void BlobPtSet::reset() {
	for (
		map<int, BlobPts *>::iterator iter = _bp.begin()
		; iter != _bp.end()
		; iter++) {
		iter->second->reset();
		_clean.push(iter->second);
	}
	_bp.clear();
}