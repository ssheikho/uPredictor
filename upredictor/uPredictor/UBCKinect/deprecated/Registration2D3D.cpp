#include "Registration2D3D.h"
#include "ArrayPt3DCollection.h"
#include "KinectFrame.h"
#include "Point3DRGB.h"

//TODO: Convert to BGRA so you can use 32-bit integer operations for copying
//		colors
Registration2D3D::Registration2D3D(
	FrameDesc &bgraFD
	, FrameDesc &depthFD
	, ArrayPt3DCollection *pts
	, int channel
	) :
	_bgraFD(bgraFD)
	, _depthFD(depthFD)
	, _pts(pts)
	, _channel(channel)
	, _nCameraPts(_depthFD.w * _depthFD.h)
	, _nColorPts(_yuyFD.w * _yuyFD.h)
	//, _cameraPts(new Point3DRGB[_nCameraPts])
	, _colorPtGridZ(new float[_nColorPts])
{

	_colorDepthMap.w = _depthFD.w;
	_colorDepthMap.h = _depthFD.h;
	_colorDepthMap.h = _yuyFD.bpp;

	zeroOut();
}

void Registration2D3D::zeroOut() {
	for (int i = 0; i < _nCameraPts; i++) {
		_colorPtGridZ[i] = -1.0;
	}
}

Registration2D3D::~Registration2D3D() {
	//delete[] _cameraPts;
	delete[] _colorPtGridZ;
}

void Registration2D3D::processKinectFrame(KinectFrame *kf) {
	zeroOut();

	cv::Mat bgr = kf->getImageChannel(0, _channel);

	ColorSpacePoint *colPts = _pts->getColorPts();
	CameraSpacePoint *camPts = _pts->getCameraPts();
	bool *colorIsGood = _pts->getColorIsGood();
	unsigned char *bgrPts = _pts->getBGR();
	memset(bgrPts, 0, _nCameraPts * sizeof(char) * 3);

	memset(colorIsGood, 0, _nCameraPts);

	float r = 1.0f, g = 1.0f, b = 1.0f;
	for (int i = 0; i < _nCameraPts; i++) {
		int y = floor(colPts[i].Y + 0.5);
		int x = floor(colPts[i].X + 0.5);

		int colorIndex = i * 3;
		long cgi = liesInColorGrid(x, y);
		if (cgi >= 0) {
			cgi *= 3;
			int ptGridIndex = y * _yuyFD.w + x;

			if (_colorPtGridZ[i] >= 0.0) {
				if (_colorPtGridZ[i] >= camPts[i].Z) {
					colorIsGood[i] = true;
					_colorPtGridZ[ptGridIndex] = camPts[i].Z;
				}
				else {
					colorIsGood[i] = false;
				}
			}
			else {
				colorIsGood[i] = true;
				_colorPtGridZ[ptGridIndex] = camPts[i].Z;
			}

			bgrPts[colorIndex] = bgr.data[cgi];
			bgrPts[colorIndex + 1] = bgr.data[cgi + 1];
			bgrPts[colorIndex + 2] = bgr.data[cgi + 2];
		}
	}
}

FrameDesc &Registration2D3D::getColorFrameDesc() {
	return _yuyFD;
}

FrameDesc &Registration2D3D::getDepthFrameDesc() {
	return _depthFD;
}

FrameDesc &Registration2D3D::getColorDepthFrameDesc() {
	return _colorDepthMap;
}

long Registration2D3D::liesInColorGrid(int x, int y) {
	long retVal = -1;
	if ((((y >= 0) && (y < _yuyFD.h)) && ((x >= 0) && (x <= _yuyFD.w))))
		retVal = y * _yuyFD.w + x;
	return retVal;
}
