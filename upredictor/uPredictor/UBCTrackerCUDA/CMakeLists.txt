project(UBCTRACKERCUDA)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

find_package(CUDA QUIET REQUIRED)

set(ubc_tracker_cuda_src
	CUDAControl.cpp
	randomSphere.cu	
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
)

cuda_add_library(
	ubctrackercuda SHARED
	${ubc_tracker_cuda_src}
)

set_property(TARGET ubctrackercuda PROPERTY CXX_STANDARD 11)
