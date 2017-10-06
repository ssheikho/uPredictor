#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Profile)
#SET(CMAKE_CXX_FLAGS "-g")  
SET(CMAKE_BUILD_TYPE Release)

include_directories (
	../libpfcomm/include
	../libplan/include
	../libplanresponse/include
	../libtiming/include
	../libworldmodel/include
	../../third-party/CHARM-S2-Project/

	../../third-party/CHARM-S3-Project/Linux/SMC/
	../../third-party/CHARM-S3-Project/Linux/DirectLink/
	../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/
)

link_directories (	
	../libpfcomm/src
	../libplan/src
	../libplanresponse/src
	../libtiming/src
	../libworldmodel/src
	../../third-party/CHARM-S2-Project/

	../../third-party/CHARM-S3-Project/Linux/SMC/
	../../third-party/CHARM-S3-Project/Linux/DirectLink/
	../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/
	../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/PACC
)

add_executable (pllookuptest
	pllookuptest.cc
)

target_link_libraries (pllookuptest
	plan
	timing
	worldmodel
	pfcomm
	planresponse

	SADB
	smc
	pacc
	directlink

	fl
	pthread
)
