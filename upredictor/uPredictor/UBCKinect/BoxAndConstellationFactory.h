#ifndef BOX_AND_CONSTELLATION_FACTORY_H
#define BOX_AND_CONSTELLATION_FACTORY_H

#include "BoxAndConstellation.h"
#include "Allocator.h"
#include "TypeFactory.h"

class BoxAndConstellationFactory : public TypeFactory<BoxAndConstellation> {
public:
	BoxAndConstellationFactory(
		UBC::Allocator<SimplePool<SubsetPt3DCollection>::PooledPtr> &alloc
		);

	BoxAndConstellation *getInstance();

protected:
	UBC::Allocator<SimplePool<SubsetPt3DCollection>::PooledPtr> &_alloc;
};

#endif