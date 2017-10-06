project(UBCCAMERA)

set(CMAKE_BUILD_TYPE Debug)

set(ubc_camera_src
	CameraModel.cpp
)

include_directories(
	../UBCColorTrackCUDA
	../UBCKinect
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
	ubccamera SHARED
	${ubc_camera_src}
)

add_library(
	ubccamera STATIC
	${ubc_camera_src}
)

set_property(TARGET ubccamera PROPERTY CXX_STANDARD 11)
