cmake_minimum_required(VERSION 2.8)

project(ChessBoard)

set(CMAKE_BUILD_TYPE Debug)

find_package( OpenCV REQUIRED )

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(chessboard_src
	#testMain.cpp
	multiKinect.cpp
	CameraCalibrator.cpp
	CloudTransformer.cpp
)

include_directories(
	../UBCDART
	../Linux/Third-Party/dart/src
	../UBCColorTrackCUDA
	../UBCGUI
	../UBCKinect/
	../UBCKinectGUI/
	../UBCSimpleGeometry/
	../UBCUtil
	../UBCCamera
	../Linux/Third-Party/libfreenect2/
	../Linux/Third-Party/libfreenect2/include/
	../Linux/Third-Party/libfreenect2/include/internal
	../Linux/Third-Party/libfreenect2/include/internal/CL
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	../ThirdParty/CERES/config/
	/usr/include
	/usr/include/eigen3
	/usr/include/opencv
	/usr/include/opencv2
	${GTK_INCLUDE_DIRS}
	${OpenCL_INCLUDE_DIRS}
	/usr/local/cuda-8.0/include
)

link_directories(/
	../UBCDART/
        ../UBCGUI/
        ../UBCKinect/
	../UBCKinectGUI/
	../UBCUtil/
	../UBCCamera
	../Linux/Third-Party/libfreenect2/lib/
	../Linux/Third-Party/dart/lib
	/usr/local/cuda-8.0/lib64
)

add_executable(
	ChessBoard
	${chessboard_src}
)

target_link_libraries(ChessBoard
	ubcgui
	ubckinectgui
	ubckinect
	ubccamera
	ubcutil
	ubcdart
	
	opencv_calib3d
	opencv_core
	opencv_features2d
	opencv_flann
	opencv_highgui
	opencv_imgproc
	#opencv_legacy
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
	OpenCL

	${OpenCL_LIBRARIES}
	freenect2

	${GTK_LDFLAGS}

	ceres
	glog
	cholmod
	blas
	lapack

	pthread
	gomp
)

set_property(TARGET ChessBoard PROPERTY CXX_STANDARD 11)
