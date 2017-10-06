#include "KinectInterface.h"
#include "KinectFrameFactory.h"

KinectInterface::KinectInterface(
	UINT64 kinectIndex
	, BodySegments &bs
	, TrackIDManager &tidm
	, ProcessingParameters &pp
	, bool pauseUntilDone
	) :
	_kinectIndex(kinectIndex)
	, _pause(true)
	, _running(false)
	, _eut(*this)
	, _frameNo(0)
	, _tareStamp(0)
	, _coordinateMapper(NULL)
	, _pauseUntilDone(pauseUntilDone)
	//, _yuyImage(1080, 1920, CV_8UC2)
{
	initializeDefaultSensor();

	_kff = new KinectFrameFactory(
		_yuyFD, _depthFD, bs, tidm, *_coordinateMapper, pp);

	_framePool = new SimplePool<KinectFrame>(*_kff, 100);

	_lastTime.dwLowDateTime = 0;
	_lastTime.dwHighDateTime = 0;
}

KinectInterface::~KinectInterface() {
	_kinectSensor->Close();
	_kinectSensor->Release();

	_frameReader->Release();

	//_colorFrameReader->Release();
	//_depthFrameReader->Release();
}

HRESULT KinectInterface::initializeDefaultSensor() {
	_yuyFD.w = 1920;
	_yuyFD.h = 1080;
	_yuyFD.bpp = 2;

	_depthFD.w = 512;
	_depthFD.h = 424;
	_depthFD.bpp = 2;

	//Find default kinect, open it, get its unique identifier.
	HRESULT hr = GetDefaultKinectSensor(&_kinectSensor);
	if (SUCCEEDED(hr)) hr = _kinectSensor->Open();
	if (SUCCEEDED(hr))
		hr = _kinectSensor->get_UniqueKinectId(256, _kinectUniqeID);

	hr = _kinectSensor->OpenMultiSourceFrameReader(
		FrameSourceTypes_Color | FrameSourceTypes_Depth |
		FrameSourceTypes_Body,
		&_frameReader);
	_frameReader->SubscribeMultiSourceFrameArrived(&_frameWH);

	//Coordinate Mapper
	if (SUCCEEDED(hr)) hr = _kinectSensor->get_CoordinateMapper(&_coordinateMapper);

	if (!SUCCEEDED(hr)) abort();

	return hr;
}

void KinectInterface::update() {
	HRESULT hr = S_OK;
	if ((_framePool->poolDepth() < 20) || (_framePool->poolSize() > 0)) {
		SimplePool<KinectFrame>::PooledPtr kf = _framePool->getInstance();
		kf->clear();

		IMultiSourceFrameArrivedEventArgs *frameArgs = NULL;
		IMultiSourceFrameReference *frameRef = NULL;
		IMultiSourceFrame *frame = NULL;
		IColorFrameReference *colorRef = NULL;
		IDepthFrameReference *depthRef = NULL;
		IBodyFrameReference *bodyRef = NULL;
		IColorFrame *colorF = NULL;
		IDepthFrame *depthF = NULL;
		IBodyFrame *bodyF = NULL;

		byte *colB = NULL;
		UINT16 *depthB = NULL;
		UINT bufSize = 0;

		WaitForSingleObject(reinterpret_cast<HANDLE>(_frameWH), INFINITE);
		hr = _frameReader->GetMultiSourceFrameArrivedEventData(_frameWH, &frameArgs);

		if (SUCCEEDED(hr)) hr = frameArgs->get_FrameReference(&frameRef);
		if (SUCCEEDED(hr)) hr = frameRef->AcquireFrame(&frame);

		if (SUCCEEDED(hr)) hr = frame->get_ColorFrameReference(&colorRef);
		if (SUCCEEDED(hr)) hr = frame->get_DepthFrameReference(&depthRef);
		if (SUCCEEDED(hr)) hr = frame->get_BodyFrameReference(&bodyRef);

		if (SUCCEEDED(hr)) hr = colorRef->AcquireFrame(&colorF);
		if (SUCCEEDED(hr)) hr = depthRef->AcquireFrame(&depthF);
		if (SUCCEEDED(hr)) hr = bodyRef->AcquireFrame(&bodyF);

		if (SUCCEEDED(hr)) hr = colorF->get_RelativeTime(&kf->_timeStamp);

		if (SUCCEEDED(hr)) hr = colorF->AccessRawUnderlyingBuffer(&bufSize, &colB);
		memcpy(kf->_yuy.data, colB, bufSize);

		if (SUCCEEDED(hr)) hr = depthF->AccessUnderlyingBuffer(&bufSize, &depthB);
		memcpy(kf->_depth.data, depthB, bufSize * 2);

		IBody *bodies[BODY_COUNT] = { 0 };
		if (SUCCEEDED(hr)) hr = bodyF->GetAndRefreshBodyData(BODY_COUNT, bodies);
		kf->_bcc.update(bodies, BODY_COUNT, _kinectIndex);

		if (frameArgs) frameArgs->Release();
		if (frameRef) frameRef->Release();
		if (frame) frame->Release();
		if (colorRef) colorRef->Release();
		if (depthRef) depthRef->Release();
		if (bodyRef) bodyRef->Release();
		if (colorF) colorF->Release();
		if (depthF) depthF->Release();
		if (bodyF) bodyF->Release();

		if (SUCCEEDED(hr)) {
			if (_frameNo % 1 == 0) {
				ExternalUpdateCollection::update();
				fireUpdate(kf);
			}
			_frameNo++;
		}
	}
}

bool KinectInterface::hasFutureUpdates() {
	return _running;
}

void KinectInterface::onStartup() {}

void KinectInterface::start() {
	_running = true;
	_eut.start();
}

void KinectInterface::join() {
	_running = false;
	_eut.stop();
}

FrameDesc &KinectInterface::getYUYFD() {
	return _yuyFD;
}

FrameDesc &KinectInterface::getDepthFD() {
	return _depthFD;
}

/*
TrackIDManager &KinectInterface::getTIDM() {
	return _tidm;
}
*/

SimplePool<KinectFrame> &KinectInterface::getKFPool() {
	return *_framePool;
}

ICoordinateMapper &KinectInterface::getCoordinateMapper() {
	return *_coordinateMapper;
}

void KinectInterface::resetTimestamps() {
	_tareStamp = GetTickCount();
}

UINT64 KinectInterface::kinectIndex() {
	return 0;
}

Pause &KinectInterface::getPause() {
	return _pause;
}

PauseUntilDone<SimplePool<KinectFrame>::PooledPtr>
	&KinectInterface::getPauseUntilDone() {
	return _pauseUntil;
}