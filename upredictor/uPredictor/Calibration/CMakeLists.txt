cmake_minimum_required(VERSION 2.8)

project(Calibration)

set(CMAKE_BUILD_TYPE Debug)

find_package( OpenCV REQUIRED )

include(FindPkgConfig)
#pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(calibration_src
	homography.cpp
)

include_directories(
	../UBCCamera
	../UBCColorTrackCUDA
	../UBCGUI
	../UBCKinect/
	../UBCKinectGUI/
	../UBCSimpleGeometry/
	../UBCUtil
	../Linux/Third-Party/libfreenect2/
	../Linux/Third-Party/libfreenect2/include/
	../Linux/Third-Party/libfreenect2/include/internal
	../Linux/Third-Party/libfreenect2/include/internal/CL
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	/usr/include/opencv
	/usr/include/opencv2
	#${GTK_INCLUDE_DIRS}
)

link_directories(/
	../UBCCamera/
        ../UBCGUI/
        ../UBCKinect/
	../UBCKinectGUI/
	../UBCUtil/
	../Linux/Third-Party/libfreenect2/lib/
)

add_executable(
	Calibration
	${calibration_src}
)

target_link_libraries(Calibration
	ubcgui
	ubckinectgui
	ubckinect
	ubcutil
	ubccamera
	
	opencv_calib3d
	opencv_core
	opencv_features2d
	opencv_flann
	opencv_highgui
	opencv_imgcodecs
	opencv_imgproc
#	opencv_legacy
	opencv_ml
	opencv_objdetect
	opencv_video
	opencv_videoio

	glfw
	GL
	GLEW
	GLU
	glut
	
	freenect2
	pthread
	#${GTK_LDFLAGS}
)

set_property(TARGET Calibration PROPERTY CXX_STANDARD 11)
