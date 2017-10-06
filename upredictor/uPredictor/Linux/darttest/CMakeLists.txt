cmake_minimum_required(VERSION 2.8.11)
project(DARTTEST)

include_directories(
	/home/justin/Research/Code/libfreenect2
	/home/justin/Research/Code/libfreenect2/include
)

link_directories(
	/home/justin/Research/Code/libfreenect2/lib
	#/usr/local/cuda-8.0/lib64
)

link_libraries(
	libfreenect2.so
	libOpenCL.so
)

add_executable(darttest darttest.cpp)
