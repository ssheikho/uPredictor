# Install script for directory: /home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/justin/charm/charm/trunk/ROS/catkin_ws/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wam_srvs/srv" TYPE FILE FILES
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerPos.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspVel.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/CartPosMove.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/JointMove.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerVel.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadPos.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/GravityComp.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/OrtnMove.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspPos.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadVel.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/Hold.srv"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/PoseMove.srv"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wam_srvs/cmake" TYPE FILE FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/build/wam_srvs/catkin_generated/installspace/wam_srvs-msg-paths.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/devel/include/wam_srvs")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/devel/share/common-lisp/ros/wam_srvs")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/justin/charm/charm/trunk/ROS/catkin_ws/devel/lib/python2.7/dist-packages/wam_srvs")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/devel/lib/python2.7/dist-packages/wam_srvs")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/build/wam_srvs/catkin_generated/installspace/wam_srvs.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wam_srvs/cmake" TYPE FILE FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/build/wam_srvs/catkin_generated/installspace/wam_srvs-msg-extras.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wam_srvs/cmake" TYPE FILE FILES
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/build/wam_srvs/catkin_generated/installspace/wam_srvsConfig.cmake"
    "/home/justin/charm/charm/trunk/ROS/catkin_ws/build/wam_srvs/catkin_generated/installspace/wam_srvsConfig-version.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wam_srvs" TYPE FILE FILES "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/package.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

