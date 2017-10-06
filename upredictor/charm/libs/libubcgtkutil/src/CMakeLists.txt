SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

SET(LIB_UBC_GTK_UTIL_SRC	
	gridwrapper.cc
	gtkutil.cc
	swwrapper.cc
	updatebutton.cc
)

add_library(ubcgtkutil SHARED ${LIB_UBC_GTK_UTIL_SRC})

include_directories (
	../include
	../../libubcutil/include
	${GTK3_INCLUDE_DIRS}
)


INSTALL(FILES libwubcgtkutil.so DESTINATION /lib)
