#include "ArrayPt3DCollectionFactory.h"

ArrayPt3DCollectionFactory::ArrayPt3DCollectionFactory(
	int nPts

	#ifdef _WIN32
	, ICoordinateMapper &cm
	#elif __linux__
	, libfreenect2::Registration &reg
	#endif

	, FrameDesc &depthFD) :
	_nPts(nPts)

	#ifdef _WIN32
	, _cm(cm)
	#elif __linux__
	, _reg(reg)
	#endif

	, _depthFD(depthFD) {}

ArrayPt3DCollection *ArrayPt3DCollectionFactory::getInstance() {
	return new ArrayPt3DCollection(_nPts
		#ifdef _WIN32
		, _cm
		#elif __linux__
		, _reg
		#endif

		, _depthFD);
}
