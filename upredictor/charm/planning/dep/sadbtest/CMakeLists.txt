#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Profile)
#SET(CMAKE_CXX_FLAGS "-g")  

include_directories (
	../libplan/include
	../libplanresponse/include
	../libtiming/include
	../libworldmodel/include
	../../third-party/CHARM-S2-Project/
)

link_directories (	
	../libplan/src
	../libpfcomm/src
	../libplanresponse/src
	../libtiming/src
	../libworldmodel/src
	../../third-party/CHARM-S2-Project/
)

add_executable (sadbtest
	sadbtest.cc
)

target_link_libraries (sadbtest
	plan
	timing
	worldmodel
	pfcomm
	planresponse

	SADB 

	fl
	pthread
)
