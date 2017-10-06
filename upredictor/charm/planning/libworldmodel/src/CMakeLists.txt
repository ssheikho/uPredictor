#include(../../NicoLinuxConfig.cmake.in)
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")				

SET(LIB_WORLDMODEL_SRC
#	planresponder.cc
	actiontoactor.cc
	actor.cc
	actoreventline.cc
	actorfactory.cc
	actorplan.cc
	actorsorter.cc
	actortable.cc
	astable.cc
	autoactor.cc
	printactor.cc
	worldmodel.cc
)

add_library(worldmodel SHARED ${LIB_WORLDMODEL_SRC})
add_library(worldmodel STATIC ${LIB_WORLDMODEL_SRC})

include_directories (
	../include
	../../libpfcomm/include
	../../libplan/include
	../../libplanresponse/include
	../../libtiming/include

	../../../third-party/CHARM-S3-Project/Linux/SMC/
	../../../third-party/CHARM-S3-Project/Linux/DirectLink/
	../../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/
)

#INSTALL(FILES libplan.so DESTINATION /lib)
