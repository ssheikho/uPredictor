SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

SET(LIB_WAM_GUI_SRC	
	armcontrolbox.cc
	cmdstrline.cc
	#gtkutil.cc	
	#gridwrapper.cc
	handcontrolbox.cc
	interpline.cc
	posgrid.cc		
	posline.cc		
	poslistcb.cc		
	safetycontrolbox.cc
	#swwrapper.cc
	#updatebutton.cc
	wamcontrolwindow.cc
	#wamjointlisten.cc
	#wamjointsub.cc
	#wamsimplemover.cc
)

add_library(wamgui SHARED ${LIB_WAM_GUI_SRC})

include_directories (
	../include
	../../libwamtiming/include/
	../../../libs/libubcutil/include
	../../../libs/libubcgtkutil/include
	../../../third-party/libbarrett-1.2.1/include/
	../../../third-party/libconfig-1.4.5/lib
	/usr/include/eigen3
	/usr/include/eigen2
	/usr/include/xenomai
	${GTK3_INCLUDE_DIRS}
)


INSTALL(FILES libwamgui.so DESTINATION /lib)
