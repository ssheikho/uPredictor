project(UBCDART)

include(${CMAKE_CURRENT_LIST_DIR}/../ProjectIncludes.cmake.in)

find_package(CUDA REQUIRED)

#set(CMAKE_BUILD_TYPE Debug)

#find_package(PkgConfig)
#pkg_check_modules(eigen3 REQUIRED eigen3)
#pkg_check_modules(tinyxml REQUIRED tinyxml)
#pkg_check_modules(matheval REQUIRED libmatheval)
#pkg_check_modules(assimp assimp)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

add_definitions(-DASSIMP_BUILD)
add_definitions(-DCUDA_BUILD)

set(ubc_dart_src
	F4VectPt3DCol.cpp
	KIBackProjector.cpp
	KIDepthSource.cpp
	KIPointCloudSource.cpp
	TrackerSliders.cpp
	TrackerUI.cpp
	UBCDARTModel.cpp
	UBCDARTModelRenderer.cpp
	UBCDARTOptimizer.cpp
	UBCDARTPredictionRenderer.cpp
	UBCDARTTracker.cpp
	UBCDARTTrackerModelRenderer.cpp

	PointCloud.cu
)

include_directories(
	../UBCCamera
	../UBCColorTrackCUDA
	../UBCGUI
	../UBCKinect
	../UBCSimpleGeometry
	../UBCUtil
	../LZ4
	../Linux/Third-Party/dart/src
	../Linux/Third-Party/dart/src/optimization
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	../Linux/Third-Party/libfreenect2/include
	../Linux/Third-Party/libfreenect2
	/usr/include
	/usr/include/opencv
	/usr/include/eigen3
	/usr/local/cuda-8.0/include

	${GTK_INCLUDE_DIRS}
)

cuda_add_library(
	ubcdart SHARED
	${ubc_dart_src}
)

cuda_add_library(
	ubcdart STATIC
	${ubc_dart_src}
)

set_property(TARGET ubcdart PROPERTY CXX_STANDARD 11)
