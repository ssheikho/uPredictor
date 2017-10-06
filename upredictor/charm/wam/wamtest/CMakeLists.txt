cmake_minimum_required(VERSION 2.8.3)
set(	CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
		"../../../../third-party/libbarrett-1.2.1/cmake/modules/")
project(wamtest)

find_package(Barrett REQUIRED)
add_definitions(${BARRETT_DEFINITIONS})

link_directories (	
	/usr/lib/x86_64-linux-gnu/
	../libwamtiming/src
	${BARRETT_LIBRARY_DIRS}
)

include_directories(
	include
	../libwamtiming/include
	/usr/include/eigen2
	/usr/include/xenomai
	#${XENOMAI_INCLUDE_DIR}
	../../third-party/libbarrett-1.2.1/src
	${catkin_INCLUDE_DIRS}
	${BARRETT_INCLUDE_DIRS}
)

add_executable(wamtest
	wamtest.cc 
)

target_link_libraries(
	wamtest
	gsl
	barrett
	BulletSoftBody
	BulletCollision
	BulletDynamics
	wamtiming
	${catkin_LIBRARIES}
	${BARRETT_LIBRARIES}
)

#catkin_package(CATKIN_DEPENDS message_runtime wam_msgs wam_srvs)

#install(TARGETS wamtest RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
