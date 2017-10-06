#include(../../NicoLinuxConfig.cmake.in)
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(scanner planscan.l planscan.yy.cc)
#BISON_TARGET(parser planscan.y planscan.tab.cc HEADER planscan.tab.hh)
# 

add_custom_command( OUTPUT planscan.tab.c planscan.tab.h
                     DEPENDS planscan.y
                     COMMAND bison planscan.y -b planscan -d
)

add_custom_command( OUTPUT planscan.tab.cc
                     DEPENDS planscan.tab.c
                     COMMAND mv planscan.tab.c planscan.tab.cc
)

add_custom_command(OUTPUT ../include/planscan.tab.h
                     DEPENDS planscan.tab.h
                     COMMAND mv planscan.tab.h ../include/planscan.tab.h
)

add_custom_target(planscanheaders ALL
				DEPENDS ../include/planscan.tab.h)
				

SET(LIB_PLAN_SRC
	action.cc
	actionmap.cc
	actionpredicate.cc
	andactionpredicate.cc
	atomicactionpredicate.cc
	concurrentactiontable.cc
	concurrentplan.cc
	concurrentplanaction.cc
	concurrentplanconcurrency.cc
	concurrentplangrid.cc
	concurrentplanline.cc
	concurrentplanstep.cc
	concurrentplantable.cc
	concurrentplantree.cc
	concurrentreplanner.cc
	conplanlentable.cc
	conplantimetable.cc
	domain.cc 
	domainmap.cc
	instanceloader.cc
	noconcurtable.cc
	notactionpredicate.cc
	objecttable.cc
	paramlist.cc
	paramlisttable.cc
	plan.cc
	planlentable.cc
	plannerutil.cc
	planninggraph.cc
	planscan.yy.cc
	planscan.tab.cc
	planstate.cc
	planstatepred.cc
	planstatepredtable.cc
	planstatetable.cc
	plantable.cc
	plantree.cc
	predicate.cc
	predicatemap.cc
	problem.cc
	replanner.cc
	timevector.cc
	typemap.cc
)

add_library(plan SHARED ${LIB_PLAN_SRC})
#add_library(plan STATIC ${LIB_PLAN_SRC})

include_directories (
	../include
	../../libplanresponse/include
	../../libtiming/include
	../../libworldmodel/include
)

#INSTALL(FILES libplan.so DESTINATION /lib)
