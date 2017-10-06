#include(../../NicoLinuxConfig.cmake.in)
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")

SET(LIB_PLANNER_CONF_SRC
	plannerconfig.cc
)

add_library(plannerconf SHARED ${LIB_PLANNER_CONF_SRC})
#add_library(plannerconf STATIC ${LIB_PLANNER_CONF_SRC})

include_directories (
	../include
	../../libplan/include
	../../libplanresponse/include
	../../libtiming/include
	../../libworldmodel/include
)

#INSTALL(FILES libplan.so DESTINATION /lib)
