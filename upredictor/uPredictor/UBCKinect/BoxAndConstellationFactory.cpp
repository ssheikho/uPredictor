#include "BoxAndConstellationFactory.h"

BoxAndConstellationFactory::BoxAndConstellationFactory(
	UBC::Allocator<SimplePool<SubsetPt3DCollection>::PooledPtr> &alloc) :
_alloc(alloc) {}

BoxAndConstellation *BoxAndConstellationFactory::getInstance() {
	return new BoxAndConstellation(_alloc.getInstance());
}