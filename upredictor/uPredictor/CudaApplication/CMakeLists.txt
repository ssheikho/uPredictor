project(CUDAPPLICATION)

set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(cuda_application_src
        #CudaApplication.cpp
)

include_directories(
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	${GTK_INCLUDE_DIRS}
)

add_library(
	cudapplication STATIC
	${cuda_application_src}
)

add_library(
	cudaapplication SHARED
	${cuda_application_src}
)

set_property(TARGET cudaapplication PROPERTY CXX_STANDARD 11)
