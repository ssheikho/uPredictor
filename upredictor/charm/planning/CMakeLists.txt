#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_CXX_FLAGS -O3)

PROJECT( PLANNER )

#Libraries
ADD_SUBDIRECTORY(libplannerconf/src)
ADD_SUBDIRECTORY(libplan/src)
ADD_SUBDIRECTORY(libplanresponse/src)
ADD_SUBDIRECTORY(libtiming/src)
ADD_SUBDIRECTORY(libworldmodel/src)

#Programs
#ADD_SUBDIRECTORY(pllookuptest)
#ADD_SUBDIRECTORY(planinteract)
ADD_SUBDIRECTORY(plannerscrew)
#ADD_SUBDIRECTORY(planrunconcur)
#ADD_SUBDIRECTORY(timevectortest)
