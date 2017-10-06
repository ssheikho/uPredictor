project(UBCGUIExample)

include(${CMAKE_CURRENT_LIST_DIR}/../ProjectIncludes.cmake.in)
#set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE(OpenCL)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -std=c++0x")

#/usr/lib/x86_64-linux-gnu/libOpenCL.so

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTK_CFLAGS}")

set(ubc_gui_example_src
	GUIExample.cpp
)

include_directories(
	../UBCCamera
	../UBCColorTrackCUDA
	../UBCDART
	../UBCGUI
	../UBCKinect/
	../UBCKinectGUI/
	../UBCSimpleGeometry/
	../UBCUtil
	../Linux/Third-Party/dart/src
	../Linux/Third-Party/libfreenect2/
	../Linux/Third-Party/libfreenect2/include/
	../Linux/Third-Party/libfreenect2/include/internal
	../Linux/Third-Party/libfreenect2/include/internal/CL
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	/usr/include/opencv
	/usr/include/opencv2
	#/usr/include/atk-1.0
	#/usr/include/cairo
	#/usr/include/eigen3
	#/usr/include/gdk-pixbuf-2.0
	#/usr/include/glib-2.0
	#/usr/include/gtk-3.0
	#/usr/include/pango-1.0
	#/usr/lib/x86_64-linux-gnu/glib-2.0/include/
	${OpenCL_INCLUDE_DIRS}
	${GTK_INCLUDE_DIRS}
	/usr/local/cuda-8.0/include
)

link_directories(
	../UBCCamera/
	../UBCColorTrackCUDA/
	../UBCDART/
	../UBCGUI/
	../UBCKinect/
	../UBCKinectGUI/
	../UBCUtil/
	../Linux/Third-Party/dart/lib
	../Linux/Third-Party/libfreenect2/lib/
	#/usr/lib/x86_64-linux-gnu/
	/usr/local/cuda-8.0/lib64
)

add_executable(
	GUIExample
	${ubc_gui_example_src}
)

target_link_libraries(GUIExample
	UBColorTrackCuda
	ubcdart
	ubckinectgui
	ubckinect
	ubccamera

	dart
	
	opencv_calib3d
	opencv_core
	opencv_features2d
	opencv_flann
	opencv_highgui
	opencv_imgproc
	opencv_legacy
	opencv_ml
	opencv_objdetect
	opencv_video

	glfw
	GL
	GLEW
	GLU
	glut

	#nvvm
	cudart
	#OpenCL

	${OpenCL_LIBRARIES}
	freenect2

	pthread

	${GTK_LDFLAGS}

	ubcgui
	ubcutil
)

set_property(TARGET GUIExample PROPERTY CXX_STANDARD 11)
