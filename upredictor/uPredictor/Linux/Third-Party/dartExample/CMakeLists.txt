project("dartExample")
cmake_minimum_required(VERSION 2.8)

if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE Release )
endif()

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/dart/CMakeModules/")

# find packages with modules
find_package(Pangolin REQUIRED)
find_package(CUDA REQUIRED)


# find packages with pkg-config
find_package(PkgConfig)
pkg_check_modules(eigen3 REQUIRED eigen3)
pkg_check_modules(matheval REQUIRED libmatheval)

set( ${Pangolin_INCLUDE_DIRS} 
../Pangolin/include
../Pangolin/src/include
 )

set( ${Pangolin_LIBRARY_DIRS} 
../Pangolin/src/libpangolin.so
 )

set( ${Pangolin_LIBRARIES} 
../Pangolin/src/libpangolin.so
 )

include_directories(
    ${Pangolin_INCLUDE_DIRS}
    ${eigen3_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/dart/src
)


link_directories(
    ${CMAKE_BINARY_DIR}
    ${Pangolin_LIBRARY_DIRS} 
    ${PROJECT_SOURCE_DIR}/dart/lib
)
link_libraries(
    ${Pangolin_LIBRARIES}
    ${matheval_LIBRARIES}
	glut
)

##########################################################################
#   Build GPU or CPU-only executable depending on cuda                   #
##########################################################################

include_directories( ${CUDA_INCLUDE_DIRS} )
include_directories(${CUDA_TOOLKIT_ROOT_DIR}/samples/common/inc)
cuda_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CUDA_NVCC_FLAGS "-arch=sm_35" "--use_fast_math"  "-O3" "--ptxas-options=--verbose") # "-fmad=false" "-DTHRUST_DEVICE_BACKEND=THRUST_DEVICE_BACKEND_OMP"
add_definitions(-DCUDA_BUILD)

set(all_sources ${sources} ${cpu_sources} ${gpu_sources})
link_directories( ${CUDA_TOOLKIT_ROOT_DIR}/lib64/)

set(DART_ROOT ${PROJECT_SOURCE_DIR}/../dart CACHE PATH "path to the dart root directory")
message(STATUS "dart is at ${DART_ROOT}")
include_directories(${DART_ROOT}/src)
link_directories(${DART_ROOT}/lib)

cuda_add_executable(
    #executable
    track_space_justin_demo
    #sources
    ${all_sources}
    #main
    track_space_justin_demo.cpp
)
target_link_libraries(track_space_justin_demo dart)


