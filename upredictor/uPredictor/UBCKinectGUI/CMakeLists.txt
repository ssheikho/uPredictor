project(UBCKINECTGUI)

set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(ubc_kinect_gui_src
        Box3DRenderer.cpp
        BoxRenderer.cpp
	CloudRenderer.cpp
	ColorRow.cpp
	#ColorSegInterface.cpp
	#ColorTrackerInterface.cpp
	CUDAColorTrackerGUI.cpp
	ImageWindowAndChannel.cpp
	KinectCloudRender.cpp
	#KinectCloudViewer.cpp
	KinectQuiverRenderer.cpp
	KinectSphereRenderer.cpp
	QuadPack.cpp
	SegmentBroadcaster.cpp
	SphereRenderer.cpp
	#SphereUI.cpp
	#TrackedObjectRenderer.cpp
	UBCRectangularPrism.cpp
)

include_directories(
    ../UBCCamera
    ../UBCColorTrackCUDA
	../UBCGUI
	../UBCKinect
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	../Linux/Third-Party/libfreenect2/include
	../Linux/Third-Party/libfreenect2/
	/usr/include
	/usr/include/eigen3
	/usr/include/nvidia-361
	/usr/include/opencv
	${GTK_INCLUDE_DIRS}
)

add_library(
	ubckinectgui STATIC
	${ubc_kinect_gui_src}
)

add_library(
	ubckinectgui SHARED
	${ubc_kinect_gui_src}
)

set_property(TARGET ubckinectgui PROPERTY CXX_STANDARD 11)
