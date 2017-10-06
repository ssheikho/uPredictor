#include(../../NicoLinuxConfig.cmake.in)
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")

SET(LIB_STATE_MACHINE_SRC
	stopwatch.cc
)

add_library(statemachine SHARED ${LIB_STATE_MACHINE_SRC})
add_library(statemachine STATIC ${LIB_STATE_MACHINE_SRC})

include_directories (
	../include
)

#INSTALL(FILES libplan.so DESTINATION /lib)
