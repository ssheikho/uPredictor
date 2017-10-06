#include "KinectVideoDecompress.h"
#include "FrameDesc.h"
#include "UBCUtil.h"

#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/highgui/highgui_c.h>

KinectVideoDecompress::KinectVideoDecompress() :
	_vc(NULL)
	, _nFrames(0)
	, _curFrame(0)
{}

#ifdef _WIN32
KinectVideoDecompress::KinectVideoDecompress(wstring fileName, FrameDesc &fd) :
#elif __linux__
KinectVideoDecompress::KinectVideoDecompress(string fileName, FrameDesc &fd) :
#endif
	_vc(NULL)
	, _nFrames(0)
	, _curFrame(0)
{
	open(fileName, fd);
}

KinectVideoDecompress::~KinectVideoDecompress() {
	close();
}

#ifdef __WIN32
bool KinectVideoDecompress::open(wstring fileName, FrameDesc &fd) {
#elif __linux__
bool KinectVideoDecompress::open(string fileName, FrameDesc &fd) {
#endif
	if (!_vc) {
		_vc = new cv::VideoCapture();
		#ifdef __WIN32
		_isOpen = _vc->open(wstringToString(fileName));
		#elif __linux__
		_isOpen = _vc->open(fileName);
		#endif
		_nFrames = _vc->get(CV_CAP_PROP_FRAME_COUNT);
	}

	if (!_isOpen) {
		delete _vc;
		_vc = NULL;
	}

	return _isOpen;
}

void KinectVideoDecompress::close() {
	if (_vc) {
		delete _vc;
		_vc = NULL;
		_nFrames = 0;
	}
}

void KinectVideoDecompress::fillInFrame(
	SimplePool<KinectFrame>::PooledPtr t
	, long index) {
	if (_isOpen) {
		_vc->set(CV_CAP_PROP_POS_FRAMES, _curFrame = index);
		//_curFrame = _vc.get(CAP_PROP_POS_FRAMES);
		_vc->read(t->_bgra);
	}
}

long KinectVideoDecompress::nFrames() {
	return _nFrames;
}

long KinectVideoDecompress::curFrame() {
	return _curFrame;
}
