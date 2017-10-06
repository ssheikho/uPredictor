SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

SET(LIB_WAM_TIMING_SRC							
	armpose.cc									
	armposelistener.cc		
	armposeinterpreter.cc			
	armposer.cc
	cmdstringinterpreter.cc	
	compoundinterpreter.cc
	defaultarmpose.cc	
	#externalupdate.cc
	handcontrol.cc
	poslist.cc		
	printarmposer.cc
	printhandcontrol.cc
	printsafetycontrols.cc
	safetycontrols.cc
	timingutil.cc
	updatethread.cc
)

add_library(wamtiming SHARED ${LIB_WAM_TIMING_SRC})
#add_library(wamtiming_static STATIC ${LIB_WAM_TIMING_SRC})

include_directories (
	../include
	../../../libs/libubcgtkutil/include
	../../../libs/libubcutil/include
	../../../third-party/libbarrett-1.2.1/include/
	../../../third-party/libconfig-1.4.5/lib
	#/usr/include/eigen3
	/usr/include/eigen2
	/usr/include/xenomai
)

INSTALL(FILES libwamtiming.so DESTINATION /lib)
