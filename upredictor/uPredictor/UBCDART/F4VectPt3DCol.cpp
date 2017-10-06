#include "F4VectPt3DCol.h"
#include "CameraModel.h"

#include <cstring>

F4VectPt3DCol::F4VectPt3DCol(CameraModel &cm) :
	_nPts(cm._height * cm._width)
	, _cameraSpacePoints(new CameraSpacePoint[_nPts])
	, _depthRGB(cm._height, cm._width, CV_8UC3)
	//, _f("./test.txt")
{
}

F4VectPt3DCol::~F4VectPt3DCol() {
	delete[] _cameraSpacePoints;
	//_f.flush();
	//_f.close();
}

void F4VectPt3DCol::update(cv::Mat &depthRGB
	, dart::MirroredVector<float4> &vertMap) {
	for(int i = 0; i < _nPts; i++) {
		//_f << vertMap[i].x << "	" << vertMap[i].y << "	" << vertMap[i].z <<
		//	"	"	 << vertMap[i].w << endl;
		_cameraSpacePoints[i].X = vertMap[i].x / vertMap[i].w;
		_cameraSpacePoints[i].Y = vertMap[i].y / vertMap[i].w;
		_cameraSpacePoints[i].Z = vertMap[i].z / vertMap[i].w;
	}

	memcpy(_depthRGB.data, depthRGB.data, _nPts * 3);
	fireUpdate(this);
}

int F4VectPt3DCol::getNPts() {
	return _nPts;
}

CameraSpacePoint *F4VectPt3DCol::getCameraPt(int index) {
	return &_cameraSpacePoints[index];
}

CameraSpacePoint *F4VectPt3DCol::getCameraPts() {
	return _cameraSpacePoints;
}

unsigned char *F4VectPt3DCol::getRGB() {
	return _depthRGB.data;
}

