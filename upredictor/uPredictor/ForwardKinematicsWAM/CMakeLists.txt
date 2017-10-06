project(ForwardKinematicsWAM)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

set(forward_kinematics_wam_src
	DH.h
	DH.cpp
	DH_Parameters.cpp
	ForwardKinematicsWAM.h
	ForwardKinematicsWAM.cpp
)

include_directories(
	/usr/include
	/usr/include/eigen3
	/usr/include/iostream
	/usr/include/math.h

)

link_directories(
	../UBCCamera/
	../UBCColorTrackCUDA/
	../UBCDART/
	../UBCGUI/
	../UBCKinect/
	../UBCKinectGUI/
	../UBCUtil/
	../Linux/Third-Party/dart/lib
	../Linux/Third-Party/libfreenect2/lib/
	/usr/lib/x86_64-linux-gnu/
	/usr/local/cuda-8.0/lib64
)



add_executable(
	ForwardKinematicsWAM
	${forward_kinematics_wam_src}
)

set_property(TARGET ForwardKinematicsWAM PROPERTY CXX_STANDARD 11)
