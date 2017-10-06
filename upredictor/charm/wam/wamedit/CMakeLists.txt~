cmake_minimum_required(VERSION 2.8.3)
project(wamedit)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

find_package(Barrett REQUIRED)
add_definitions(${BARRETT_DEFINITIONS})


link_directories (
	../libwamtiming/src/
	../../libs/libubcutil/src
	../../libs/libubcgtkutil/src
	#../../third-party/libbarrett-1.2.1/
	/usr/lib/x86_64-linux-gnu/
)

include_directories(
	include
	../libwamgui/include
	../libwamtiming/include
	../../libs/libubcutil/include
	../../libs/libubcgtkutil/include
	${GTK3_INCLUDE_DIRS}
	${BARRETT_INCLUDE_DIRS}	
)

add_executable(wamedit
	wamedit.cc 
)

target_link_libraries(
	wamedit
	gsl
	#barrett
	BulletSoftBody
	BulletCollision
	BulletDynamics
	wamgui
	wamtiming
	ubcutil
	ubcgtkutil
	${catkin_LIBRARIES}
	${BARRETT_LIBRARIES}
	${GTK3_LIBRARIES}
)

#catkin_package(CATKIN_DEPENDS message_runtime wam_msgs wam_srvs)

#install(TARGETS wamtest RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
