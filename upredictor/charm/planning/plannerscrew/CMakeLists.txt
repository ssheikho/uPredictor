#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Profile)
#SET(CMAKE_CXX_FLAGS "-g")  
#SET(CMAKE_BUILD_TYPE Release)

#ADD_FLEX_BISON_DEPENDENCY(scanner parser)

include_directories (
	../libplan/include
	../libplannerconf/include
	../libplanresponse/include
	../libtiming/include
	../libworldmodel/include
)

link_directories (	
	../libplan/src
	../libplannerconf/src
	../libplanresponse/src
	../libtiming/src
	../libworldmodel/src

	../../third-party/CHARM-S3-Project/Linux/SMC/
	../../third-party/CHARM-S3-Project/Linux/DirectLink/
	../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/PACC
)

add_executable (plannerscrew
	plannerscrew.cc
)

target_link_libraries (plannerscrew
	plan
	timing
	worldmodel
	plannerconf
	planresponse

	smc
	directlink
	pacc

	fl
	pthread
)
