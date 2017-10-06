#include "KinectFrameFactory.h"
#include "KinectFrame.h"

KinectFrameFactory::KinectFrameFactory(
	FrameDesc &yuyFD
	, FrameDesc &depthFD
	//, BodySegments &bs
	, TrackIDManager &tidm

	#ifdef _WIN32
		, ICoordinateMapper &cm
	#elif __linux__
		, libfreenect2::Registration &frereg
	#endif

	//, ProcessingParameters &pp
	) :
	_yuyFD(yuyFD)
	, _depthFD(depthFD)
	//, _bs(bs)
	, _tidm(tidm)

	#ifdef _WIN32
		, _cm(cm)
	#elif __linux__
		, _frereg(frereg)
	#endif

	//, _pp(pp)
{}

KinectFrameFactory::~KinectFrameFactory() {}

KinectFrame *KinectFrameFactory::getInstance() {
	return new KinectFrame(_yuyFD, _depthFD
		//, _bs
		, _tidm

		#ifdef _WIN32
			, _cm
		#elif __linux__
			, _frereg
		#endif

		//, _pp
		);
}
