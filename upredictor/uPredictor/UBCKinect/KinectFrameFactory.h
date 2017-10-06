#ifndef KINECT_FRAME_FACTORY_H
#define KINECT_FRAME_FACTORY_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "registration.h"
#endif

#include "Allocator.h"
#include "TypeFactory.h"

//class BodySegments;
class KinectFrame;
//class ProcessingParameters;
class TrackIDManager;
struct FrameDesc;

class KinectFrameFactory : public TypeFactory<KinectFrame> {
public:
	KinectFrameFactory(
		FrameDesc &yuyFD
		, FrameDesc &depthFD
		, TrackIDManager &tidm

		#ifdef _WIN32
			, ICoordinateMapper &cm
		#elif __linux__
			, libfreenect2::Registration &frereg
		#endif

		//, ProcessingParameters &pp
		);
	~KinectFrameFactory();

	KinectFrame *getInstance();

protected:
	FrameDesc &_yuyFD, &_depthFD;
	//BodySegments &_bs;
	TrackIDManager &_tidm;

	#ifdef _WIN32
		ICoordinateMapper &_cm;
	#elif __linux__
		libfreenect2::Registration &_frereg;
	#endif

	//ProcessingParameters &_pp;
};

#endif
