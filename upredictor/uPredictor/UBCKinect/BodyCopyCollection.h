#ifndef BODY_COPY_COLLECTION_H
#define BODY_COPY_COLLECTION_H

#include "BodyCopy.h"

class BodyCopyCollection {
public:
	BodyCopyCollection(
		BodySegments &bs
		, TrackIDManager &tidm
		);
	~BodyCopyCollection();

	void update(IBody **body, int nBodies, UINT64 kinectIndex);

	size_t getNStored();
	size_t getNTracked();

	BodyCopy *getBC(size_t index);

protected:
	size_t _nStored;
	BodyCopy *_bc[BODY_COUNT];
};

#endif