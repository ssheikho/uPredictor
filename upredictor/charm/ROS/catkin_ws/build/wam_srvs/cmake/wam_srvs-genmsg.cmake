# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "wam_srvs: 0 messages, 12 services")

set(MSG_I_FLAGS "-Igeometry_msgs:/opt/ros/hydro/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(wam_srvs_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/GravityComp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/CartPosMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/Hold.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/JointMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/PoseMove.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/OrtnMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)
_generate_srv_cpp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
)

### Generating Module File
_generate_module_cpp(wam_srvs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(wam_srvs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(wam_srvs_generate_messages wam_srvs_generate_messages_cpp)

# target for backward compatibility
add_custom_target(wam_srvs_gencpp)
add_dependencies(wam_srvs_gencpp wam_srvs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wam_srvs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/GravityComp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/CartPosMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/Hold.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/JointMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/PoseMove.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/OrtnMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)
_generate_srv_lisp(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
)

### Generating Module File
_generate_module_lisp(wam_srvs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(wam_srvs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(wam_srvs_generate_messages wam_srvs_generate_messages_lisp)

# target for backward compatibility
add_custom_target(wam_srvs_genlisp)
add_dependencies(wam_srvs_genlisp wam_srvs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wam_srvs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/GravityComp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/CartPosMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/Hold.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandGraspPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/JointMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/PoseMove.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadPos.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandFingerVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/OrtnMove.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)
_generate_srv_py(wam_srvs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/BHandSpreadVel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
)

### Generating Module File
_generate_module_py(wam_srvs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(wam_srvs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(wam_srvs_generate_messages wam_srvs_generate_messages_py)

# target for backward compatibility
add_custom_target(wam_srvs_genpy)
add_dependencies(wam_srvs_genpy wam_srvs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wam_srvs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_srvs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(wam_srvs_generate_messages_cpp geometry_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_srvs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(wam_srvs_generate_messages_lisp geometry_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_srvs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(wam_srvs_generate_messages_py geometry_msgs_generate_messages_py)
