#include "KinectInterface.h"
#include "KinectFrameFactory.h"

KinectInterface::KinectInterface(TrackIDManager &tidm, string serial) :
	_pause(true)
	, _running(false)
	, _eut(*this)
	, _frameNo(0)
	, _kinectSensor(NULL) 
	, _pipeline(NULL) 
	, _coordinateMapper(NULL)
	, _listener(NULL)
	, _frames(NULL)
	, _depthCM(NULL) {

	_serial = (serial == "") ? _freenect2.getDefaultDeviceSerialNumber() : serial;
	initializeSensor();

	_kff = new KinectFrameFactory(_bgraFD, _depthFD, tidm, *_coordinateMapper);

	_framePool = new SimplePool<KinectFrame>(*_kff, 100);
}

KinectInterface::~KinectInterface() {
	delete _coordinateMapper;
	delete _pipeline;
	delete _kinectSensor;
	delete _depthCM;
}

void KinectInterface::initializeSensor() {
	_bgraFD.w = 1920;
	_bgraFD.h = 1080;
	_bgraFD.bpp = 4;

	_depthFD.w = 512;
	_depthFD.h = 424;
	_depthFD.bpp = 4;

	_pipeline = new libfreenect2::CudaPacketPipeline(-1);
	//_pipeline = new libfreenect2::CpuPacketPipeline();

	//cout << "_serial:	" << _serial << endl;
	_kinectSensor = _freenect2.openDevice(_serial, _pipeline);

	_listener = new libfreenect2::SyncMultiFrameListener(
		//libfreenect2::Frame::Ir |
		libfreenect2::Frame::Color |
		libfreenect2::Frame::Depth);
	_frames = new libfreenect2::FrameMap();

	_kinectSensor->start();
	_kinectSensor->startStreams(true, true);

	_coordinateMapper = new libfreenect2::Registration(
		_kinectSensor->getIrCameraParams()
		, _kinectSensor->getColorCameraParams());

	_kinectSensor->setColorFrameListener(_listener);
	_kinectSensor->setIrAndDepthFrameListener(_listener);

	libfreenect2::Freenect2Device::IrCameraParams params =
		_kinectSensor->getIrCameraParams();
	_depthCM = new CameraModel(&params, _depthFD);

	//std::cout << "device serial: " << _kinectSensor->getSerialNumber() <<
	//	std::endl;
	//std::cout << "device firmware: " << _kinectSensor->getFirmwareVersion() <<
	//	std::endl;
}

void KinectInterface::update() {
	//cout << "update" << endl;
	if ((_framePool->poolDepth() < 20) || (_framePool->poolSize() > 0)) {
		//cout << "update:A" << endl;
		SimplePool<KinectFrame>::PooledPtr kf = _framePool->getInstance();
		kf->clear();

		//cout << "update:B" << endl;
		_listener->waitForNewFrame(*_frames, 10*1000);
		libfreenect2::Frame *rgb = (*_frames)[libfreenect2::Frame::Color];
		libfreenect2::Frame *depth = (*_frames)[libfreenect2::Frame::Depth];

		kf->_timeStamp = rgb->timestamp;

		memcpy(kf->_bgraF.data, rgb->data, rgb->width * rgb->height *
			rgb->bytes_per_pixel);
		memcpy(kf->_depthF.data, depth->data, depth->width * depth->height *
			depth->bytes_per_pixel);
		_listener->release(*_frames);

		//cout << "update:	" << depth->width << "	" << depth->height << "	"
		//	<< depth->bytes_per_pixel << endl;

		//kf->convertHDBGRAToRGBA();

		kf->convertHDBGRAToRGB();
		kf->convertRegBGRAToRGB();

		kf->computeRegistration();
		kf->undistortDepth();
		kf->computeDepthCameraSpacePts();

		//cout << "update:D" << endl;

		_recipients.update();
		fireUpdate(kf);
		_frameNo++;
	}
	//cout << "/update" << endl;
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

FrameDesc &KinectInterface::getBGRAFD() {
	return _bgraFD;
}

FrameDesc &KinectInterface::getDepthFD() {
	return _depthFD;
}

CameraModel &KinectInterface::getDepthCM() {
	return *_depthCM;
}

SimplePool<KinectFrame> &KinectInterface::getKFPool() {
	return *_framePool;
}

libfreenect2::Registration &KinectInterface::getCoordinateMapper() {
	return *_coordinateMapper;
}

Pause &KinectInterface::getPause() {
	return _pause;
}

ExternalUpdateCollection &KinectInterface::getRecipients() {
	return _recipients;
}
