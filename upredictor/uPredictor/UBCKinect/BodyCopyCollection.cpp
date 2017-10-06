#include "BodyCopyCollection.h"

BodyCopyCollection::BodyCopyCollection(
	BodySegments &bs
	, TrackIDManager &tidm) :
	_nStored(0)
{
	for (int i = 0; i < BODY_COUNT; i++)
		_bc[i] = new BodyCopy(bs, tidm);
}

BodyCopyCollection::~BodyCopyCollection() {}

void BodyCopyCollection::update(IBody **body, int nBodies, UINT64 kinectIndex) {
	if (nBodies > BODY_COUNT) {
		abort();
	}
	else {
		for (_nStored = 0; _nStored < nBodies; _nStored++) {
			_bc[_nStored]->update(body[_nStored], kinectIndex);
		}
	}
};

size_t BodyCopyCollection::getNStored() {
	return _nStored;
}

size_t BodyCopyCollection::getNTracked() {
	size_t retVal = 0;
	for (size_t i = 0; i < _nStored; i++)
		if (_bc[i]->getIsTracked())
			retVal++;

	return retVal;
}

BodyCopy *BodyCopyCollection::getBC(size_t index) {
	return _bc[index];
}