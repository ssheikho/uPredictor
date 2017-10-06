#include(../../NicoLinuxConfig.cmake.in)
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")

SET(LIB_SMC_COMM_SRC
	lamecomm.cc

	#stopwatch.cc
	outmessageevent.cc
	pfconfig.cc
	pfperson.cc
	smcconnection.cc

	#Event Model
	smceventmodel.cc

	#Events
	smcgetpartevent.cc
	smcmovebackevent.cc
	smcmovetopersonevent.cc
	smcstarthandoverevent.cc

	#Event Model Table
	smcemt.cc

	smcmessagehandler.cc
	smcpersonactor.cc
	smcresponseactor.cc

	messagemaker.cc

)

add_library(pfcomm SHARED ${LIB_SMC_COMM_SRC})
add_library(pfcomm STATIC ${LIB_SMC_COMM_SRC})

include_directories (
	../include
	../../libplan/include
	../../libplanresponse/include
	../../libtiming/include
	../../libworldmodel/include
	../../../third-party/CHARM-S3-Project/Linux/SMC/
	../../../third-party/CHARM-S3-Project/Linux/DirectLink/
	../../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/
)

#INSTALL(FILES libplan.so DESTINATION /lib)
