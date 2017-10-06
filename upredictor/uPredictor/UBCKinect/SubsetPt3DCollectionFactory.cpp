#include "SubsetPt3DCollectionFactory.h"

SubsetPt3DCollectionFactory::SubsetPt3DCollectionFactory(int maxPts) :
	_maxPts(maxPts) {}

SubsetPt3DCollectionFactory::~SubsetPt3DCollectionFactory() {}

SubsetPt3DCollection *SubsetPt3DCollectionFactory::getInstance() {
	return new SubsetPt3DCollection(_maxPts);
}