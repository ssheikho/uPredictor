#ifndef BOX_AND_CONSTELLATION_H
#define BOX_AND_CONSTELLATION_H

#include "Allocator.h"
#include "SubsetPt3DCollection.h"
#include "RegisteredBB.h"
#include "SimplePool.h"


class BoxAndConstellation {
public:
	BoxAndConstellation(SimplePool<SubsetPt3DCollection>::PooledPtr pts);
	~BoxAndConstellation();

	RegisteredBB &getBB();
	SimplePool<SubsetPt3DCollection>::PooledPtr getPts();

protected:
	RegisteredBB _bb;
	SimplePool<SubsetPt3DCollection>::PooledPtr _pts;
};

#endif