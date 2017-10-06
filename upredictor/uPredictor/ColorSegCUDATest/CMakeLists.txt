project(COLORSEGCUDATEST)

set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(color_seg_cuda_test_src
        #ColorSegCUDATest.cpp
        #CUDAColorSegInterface.cpp
	#CUDAControl.cpp
	#CUDANormalField.cpp
	#CUDASphereGridFilter.cpp
)

include_directories(
        ../UBCKinect
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	${GTK_INCLUDE_DIRS}
)

add_library(
	colorsegcudatest STATIC
	${color_seg_cuda_test_src}
)

add_library(
	colorsegcudatest SHARED
	${color_seg_cuda_test_src}
)

set_property(TARGET colorsegcudatest PROPERTY CXX_STANDARD 11)
