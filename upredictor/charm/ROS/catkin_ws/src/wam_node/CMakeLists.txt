cmake_minimum_required(VERSION 2.8.3)
project(wam_node)

#find_package(Eigen2 REQUIRED)

find_package(catkin
	REQUIRED COMPONENTS
	message_generation geometry_msgs wam_msgs wam_srvs roscpp)
# std_msgs sensor_msgs

#catkin_package(
#	INCLUDE_DIRS include
#)

include_directories(
	include
	../../../../third-party/libbarrett-1.2.1/include/
	#/usr/include/bullet
	/usr/include/eigen2
	/usr/include/xenomai
	#${EIGEN2_INCLUDE_DIR}
	${catkin_INCLUDE_DIRS}
)

link_directories(
	../../../../third-party/libbarrett-1.2.1/src/
)
	
# Declare the service files to be built
add_executable(wam_node
	src/wam_node.cpp
)

target_link_libraries(wam_node
	${catkin_LIBRARIES}
	barrett
	gsl
)

# Declare that this catkin package's runtime dependencies
catkin_package(CATKIN_DEPENDS message_runtime)
# std_msgs sensor_msgs
