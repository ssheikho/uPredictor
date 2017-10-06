# Install script for directory: C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/x64/vc12/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/build/lib/Debug/opencv_core2411d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/x64/vc12/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/build/lib/Release/opencv_core2411.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libs")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/x64/vc12/bin" TYPE SHARED_LIBRARY FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/build/bin/Debug/opencv_core2411d.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/x64/vc12/bin" TYPE SHARED_LIBRARY FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/build/bin/Release/opencv_core2411.dll")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/affine.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/cuda_devptrs.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/devmem2d.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/eigen.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/gpumat.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/internal.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/mat.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/opengl_interop.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/opengl_interop_deprecated.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/operations.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/version.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/wimage.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/core_c.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/core" TYPE FILE FILES "C:/Users/sara__000/predictionNew/Predictor/ThirdParty/opencv/sources/modules/core/include/opencv2/core/types_c.h")
endif()

