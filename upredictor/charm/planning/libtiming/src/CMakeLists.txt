
SET(LIB_TIMING_SRC
	stopwatch.cc
)

add_library(timing SHARED ${LIB_TIMING_SRC})
add_library(timing STATIC ${LIB_TIMING_SRC})

include_directories (
	../include
)

#INSTALL(FILES libplan.so DESTINATION /lib)
