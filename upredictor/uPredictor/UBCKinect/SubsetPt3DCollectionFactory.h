#ifndef SUBSET_PT_3D_COLLECTION_FACTORY_H
#define SUBSET_PT_3D_COLLECTION_FACTORY_H

#include "SubsetPt3DCollection.h"
#include "TypeFactory.h"

class SubsetPt3DCollectionFactory : public TypeFactory<SubsetPt3DCollection> {
public:
	SubsetPt3DCollectionFactory(int maxPts);
	~SubsetPt3DCollectionFactory();

	SubsetPt3DCollection *getInstance();

protected:
	int _maxPts;
};

#endif