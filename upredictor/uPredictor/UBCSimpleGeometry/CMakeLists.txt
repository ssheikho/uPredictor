project(UBCSIMPLEGEOMETRY)

set(CMAKE_BUILD_TYPE Debug)

set(ubc_simple_geometry_src
	UBCSimpleGeometry.c
)

include_directories(
	#../UBCColorTrackCUDA
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	../Linux/Third-Party/libfreenect2/include
	../Linux/Third-Party/libfreenect2
	/usr/include
	/usr/include/opencv
	/usr/include/eigen3
)

add_library(
	ubcsimplegeometry SHARED
	${ubc_simple_geometry_src}
)

add_library(
	ubcsimplegeometry STATIC
	${ubc_simple_geometry_src}
)

set_property(TARGET ubcsimplegeometry PROPERTY CXX_STANDARD 11)
