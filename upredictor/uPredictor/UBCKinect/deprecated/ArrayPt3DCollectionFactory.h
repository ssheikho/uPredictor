#ifndef ARRAY_PT3D_COLLECTION_FACTORY_H
#define ARRAY_PT3D_COLLECTION_FACTORY_H

#include "ArrayPt3DCollection.h"
#include "TypeFactory.h"

class ArrayPt3DCollectionFactory : public TypeFactory<ArrayPt3DCollection> {
public:
	ArrayPt3DCollectionFactory(
		int nPts
		#ifdef _WIN32
		, ICoordinateMapper &cm
		#elif __linux__
		, libfreenect2::Registration &reg
		#endif
		, FrameDesc &depthFD);

	ArrayPt3DCollection *getInstance();

protected:
	int _nPts;

	#ifdef _WIN32
	ICoordinateMapper &_cm;
	#elif __linux__
	libfreenect2::Registration &_reg;
	#endif

	FrameDesc &_depthFD;
};

#endif
