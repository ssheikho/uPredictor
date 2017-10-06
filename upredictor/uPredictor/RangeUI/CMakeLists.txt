project(RANGEUI)

set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(range_ui_src
        #RangeInterface.cpp
        #RangeUI.cpp
)

include_directories(
        ../UBCGUI
        ../UBCKinect
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	${GTK_INCLUDE_DIRS}
)

add_library(
	rangeui STATIC
	${range_ui_src}
)

add_library(
	rangeui SHARED
	${range_ui_src}
)

set_property(TARGET rangeui PROPERTY CXX_STANDARD 11)
