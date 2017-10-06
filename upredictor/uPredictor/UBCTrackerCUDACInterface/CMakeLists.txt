project(UBCTRACKERCUDACINTERFACE)

set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(ubc_tracker_cuda_c_interface_src
        #CudaFunctions.cpp
)

include_directories(
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	${GTK_INCLUDE_DIRS}
)

add_library(
	ubctrackercudacinterface STATIC
	${ubc_tracker_cuda_c_interface_src}
)

add_library(
	ubctrackercudacinterface SHARED
	${ubc_tracker_cuda_c_interface_src}
)

set_property(TARGET ubctrackercudacinterface PROPERTY CXX_STANDARD 11)
