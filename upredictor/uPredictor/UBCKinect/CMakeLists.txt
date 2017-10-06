project(UBCKINECT)

set(CMAKE_BUILD_TYPE Debug)

set(ubc_kinect_src
	ArrayPt3DCollection.cpp
	BoxAndConstellation.cpp
	BoxAndConstellationFactory.cpp
	FrameRateCounter.cpp
	KFBGRChannel.cpp
	KinectFrame.cpp
	KinectFrameFactory.cpp
	KinectImageSaver.cpp
	KinectInterface.cpp
	KinectVideoCompress.cpp
	KinectVideoDecompress.cpp
	PtSubset.cpp
	RecNameCollection.cpp
	RegisteredBB.cpp
	SphereDetectorInfo.cpp
	ThreeDBB.cpp
	TrackIDManager.cpp
)

include_directories(
	../UBCCamera
	../UBCColorTrackCUDA
	../UBCSimpleGeometry
	../UBCUtil
	../LZ4
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	../Linux/Third-Party/libfreenect2/include
	../Linux/Third-Party/libfreenect2
	/usr/include
	/usr/include/opencv
	/usr/include/eigen3
)

add_library(
	ubckinect SHARED
	${ubc_kinect_src}
)

add_library(
	ubckinect STATIC
	${ubc_kinect_src}
)

set_property(TARGET ubckinect PROPERTY CXX_STANDARD 11)
