SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

SET(LIB_UBC_UTIL_SRC	
	DefaultIntValueArray.cc
	#ExternalUpdateThread.cc
	IntegerIndicator.cc
	#IntValueArray.cc
	IntValueArrayMultiplexer.cc
	#StopWatch.cc
	#UBCUtil.cc
)

add_library(ubcutil SHARED ${LIB_UBC_UTIL_SRC})

include_directories (
	../include
	#${GTK3_INCLUDE_DIRS}
)


INSTALL(FILES libubcutil.so DESTINATION /lib)
