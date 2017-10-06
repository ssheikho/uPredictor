#include(../../NicoLinuxConfig.cmake.in)
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")				

SET(LIB_PLAN_INTERACT_SRC
	actionexecutor.cc
	concurrentplanresponder.cc
	planresponder.cc
	whenplandone.cc
#	worldmodel.cc
)

add_library(planresponse SHARED ${LIB_PLAN_INTERACT_SRC})
add_library(planresponse STATIC ${LIB_PLAN_INTERACT_SRC})

include_directories (
	../include
	../../libplan/include
	../../libtiming/include
	../../libworldmodel/include
)

#INSTALL(FILES libplan.so DESTINATION /lib)
