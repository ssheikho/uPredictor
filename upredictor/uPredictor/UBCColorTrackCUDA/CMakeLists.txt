project(UBColorTrackCuda)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

find_package(CUDA QUIET REQUIRED)

set(ubc_color_track_cuda_src
	CUDAColorSegInterface.cpp
	SphereTrack.cu	
	UBCColorTrackerCUDA.cu
)

include_directories(
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

cuda_add_library(
	UBColorTrackCuda SHARED
	${ubc_color_track_cuda_src}
)

#cuda_add_library(
#	UBColorTrackCuda STATIC
#	${ubc_color_track_cuda_src}
#)

set_property(TARGET UBColorTrackCuda PROPERTY CXX_STANDARD 11)
