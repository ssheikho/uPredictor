#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")

SET(LIB_TIMING_GUI_SRC	
	
)

add_library(timinggui SHARED ${LIB_TIMING_GUI_SRC})
add_library(timinggui_static STATIC ${LIB_TIMING_GUI_SRC})

include_directories (
	../include
)


INSTALL(FILES libtiminggui.so DESTINATION /lib)
