#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Profile)
#SET(CMAKE_CXX_FLAGS "-g")  
SET(CMAKE_BUILD_TYPE Release)

include_directories (
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
	../libplan/src
	../libpfcomm/src
	../libplanresponse/src
	../libtiming/src
	../libworldmodel/src
	../../third-party/CHARM-S2-Project/

	../../third-party/CHARM-S3-Project/Linux/SMC/
	../../third-party/CHARM-S3-Project/Linux/DirectLink/
	../../third-party/CHARM-S3-Project/Libraries/Linux/pacc-1.3.7/
)

add_executable (fakesensor
	fakesensor.cc
)

target_link_libraries (fakesensor
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
