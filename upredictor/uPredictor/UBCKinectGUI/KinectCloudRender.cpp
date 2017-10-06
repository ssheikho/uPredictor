#include "KinectCloudRender.h"
//#include "Point3DRGB.h"
//#include "Registration2D3D.h"

//#include <opencv2/opencv.hpp>
#include <GL/gl.h>

#include <cmath>
#include <iostream>

using namespace std;

KinectCloudRender::KinectCloudRender(
	KR_MODE mode
	//, UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc
	, size_t maxPts
	, int ptSize, GLubyte alpha) :
	CloudRenderer(maxPts, ptSize, alpha)
	//_kf(alloc.getInstance())
	//,
	, _mode(mode)
{}

KinectCloudRender::~KinectCloudRender() {}

void KinectCloudRender::processType(SimplePool<KinectFrame>::PooledPtr kf) {
	#ifdef _WIN32	
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	ArrayPt3DCollection &reg = kf->getRegisteredPts();

	switch (_mode) {
		case KR_COLOR_CLOUD_MODE:
		case KR_SEGMENT_CLOUD_MODE:
			{
				_nPts = reg.getNPts();
				if (_nPts > _maxPts) _nPts = _maxPts;
				memcpy(_cameraSpacePoints, reg.getCameraPts()
					, _nPts * sizeof(CameraSpacePoint));
				//memcpy(_colorIsGood, reg.getColorIsGood()
				//	, _nPts * sizeof(bool));
				memcpy(_rgbx.data, reg.getRGB()
					, _nPts * 3 * sizeof(unsigned char));
				//cv::cvtColor(_bgr, _bgr, CV_BGR2RGB);
			}
			break;
	}
	
	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void KinectCloudRender::onStartup() {}
