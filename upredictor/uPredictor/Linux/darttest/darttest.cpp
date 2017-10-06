
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/registration.h>

#include <iostream>
#include <string>

int main(int argc, char **argv) {
	libfreenect2::Freenect2 freenect2;

	libfreenect2::PacketPipeline *pipeline =
		new libfreenect2::CudaPacketPipeline(-1);
	if(!pipeline) abort();

	std::string serial = freenect2.getDefaultDeviceSerialNumber();
	libfreenect2::Freenect2Device *kinectDev =
		freenect2.openDevice(serial, pipeline);

	int types = libfreenect2::Frame::Color | libfreenect2::Frame::Depth;
	libfreenect2::SyncMultiFrameListener listener(types);

	kinectDev->setColorFrameListener(&listener);
	kinectDev->setIrAndDepthFrameListener(&listener);

	libfreenect2::Registration* registration =
		new libfreenect2::Registration(
			kinectDev->getIrCameraParams(), kinectDev->getColorCameraParams());

	kinectDev->start();

	PointXYZ *pts = new PointXYZ[512 * 424];
	while(true) {
		libfreenect2::FrameMap frames;
		libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);
		listener.waitForNewFrame(frames, 10*1000);
		libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
		libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
		registration->apply(rgb, depth, &undistorted, &registered);
		registration->getPointsXYZ(&undistorted, pts, 424, 512);
	}

	kinectDev->stop();
	kinectDev->close();

	return 0;
}
