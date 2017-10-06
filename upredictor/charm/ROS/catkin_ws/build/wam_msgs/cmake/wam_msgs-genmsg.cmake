# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "wam_msgs: 7 messages, 0 services")

set(MSG_I_FLAGS "-Iwam_msgs:/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(wam_msgs_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTCartPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTPose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTOrtnVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTOrtnPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTJointVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTCartVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)
_generate_msg_cpp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTJointPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(wam_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(wam_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(wam_msgs_generate_messages wam_msgs_generate_messages_cpp)

# target for backward compatibility
add_custom_target(wam_msgs_gencpp)
add_dependencies(wam_msgs_gencpp wam_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wam_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTCartPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTPose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTOrtnVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTOrtnPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTJointVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTCartVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)
_generate_msg_lisp(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTJointPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(wam_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(wam_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(wam_msgs_generate_messages wam_msgs_generate_messages_lisp)

# target for backward compatibility
add_custom_target(wam_msgs_genlisp)
add_dependencies(wam_msgs_genlisp wam_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wam_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTCartPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTPose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTOrtnVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTOrtnPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTJointVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTCartVel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)
_generate_msg_py(wam_msgs
  "/home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_msgs/msg/RTJointPos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(wam_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(wam_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(wam_msgs_generate_messages wam_msgs_generate_messages_py)

# target for backward compatibility
add_custom_target(wam_msgs_genpy)
add_dependencies(wam_msgs_genpy wam_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wam_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wam_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wam_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wam_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
