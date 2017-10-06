#include "KIPointCloudSource.h"

//#include "img_proc/bilateral_filter.h"

#include <iostream>

KIPointCloudSource::KIPointCloudSource(
	CameraModel &cm
	, KIDepthSource *depthSource) :
    _depthSource(depthSource)
    , _cm(cm)
	, _backProjector(_cm)
	, _nPts(_cm._width * _cm._height)
	, _pts(_cm) {
    float w = depthSource->getDepthWidth();
    float h = depthSource->getDepthHeight();

	cout << "w:	" << w << "	" << h << endl;

    cudaMalloc(&_dFilteredDepth,w*h*sizeof(float));
    cudaMalloc(&_segs,w*h*sizeof(int));

    _vertMap = new dart::MirroredVector<float4>(w*h);
    _normMap = new dart::MirroredVector<float4>(w*h);

    _vertsOnHost = _normsOnHost = false;

    _filteredVerts = false;
    _filteredNorms = false;

    _sigmaDepth = 0.10/_depthSource->getScaleToMeters();
    _sigmaPixels = 3.0;

    //projectDepthMap();
}

void KIPointCloudSource::processType(SimplePool<KinectFrame>::PooledPtr t) {
	CameraSpacePoint *cameraSpacePoints = t->_pts.getCameraPts();
	_vertsOnHost = _normsOnHost = false;
	//_depthSource->advance();
	_depthSource->processType(t);
	cudaMemcpy(_segs,t->_sdi._depthSegMap
		,_cm._width * _cm._height*sizeof(float),cudaMemcpyHostToDevice);

	projectDepthMap();
	_vertMap->syncDeviceToHost();

	_pts.update(t->_depthRGB, *_vertMap);
}

void KIPointCloudSource::onStartup() {}

void KIPointCloudSource::projectDepthMap() {
	if (_filteredNorms) {
		dart::bilateralFilter(
			_depthSource->getDeviceDepth()
			,_dFilteredDepth
			, _depthSource->getDepthWidth()
			,_depthSource->getDepthHeight(),
			_sigmaPixels,_sigmaDepth);

		_backProjector.backProjectDepthMap(_dFilteredDepth,
			_vertMap->devicePtr(), _segs);

		dart::verticesToNormals(_vertMap->devicePtr(),_normMap->devicePtr()
			,_depthSource->getDepthWidth(),_depthSource->getDepthHeight());

		if (!_filteredVerts) {
			_backProjector.backProjectDepthMap(_depthSource->getDeviceDepth(),
				_vertMap->devicePtr(), _segs);
		}
	} else {
		_backProjector.backProjectDepthMap(_depthSource->getDeviceDepth(),
			_vertMap->devicePtr(), _segs);

		dart::verticesToNormals(_vertMap->devicePtr(),_normMap->devicePtr()
			,_depthSource->getDepthWidth(),_depthSource->getDepthHeight());
	}

	//for(int i = 0; i < 100; i++) {
	//	cout << _vertMap->hostPtr()[i].w << endl;
	//}
}
