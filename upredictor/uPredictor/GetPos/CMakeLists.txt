project(GetPos)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

set(get_pos_src
	GetPos.h
	GetPos.cpp
)

include_directories(
	/usr/include
	/usr/include/eigen3
	/usr/include/iostream
	/usr/include/math.h
	/usr/local/include/c++/5.3.0

)

add_executable(
	GetPos
	${get_pos_src}
)

set_property(TARGET GetPos PROPERTY CXX_STANDARD 11)
