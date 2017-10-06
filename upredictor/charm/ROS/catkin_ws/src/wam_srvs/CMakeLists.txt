cmake_minimum_required(VERSION 2.8.3)
project(wam_srvs)
find_package(catkin REQUIRED COMPONENTS message_generation geometry_msgs)
# std_msgs sensor_msgs

# Declare the message files to be built

#add_message_files(
#	DIRECTORY msg
#	FILES
#		RTCartPos.msg
#		RTJointPos.msg
#		RTOrtnPos.msg
#		RTPose.msg
#		RTCartVel.msg
#		RTJointVel.msg
#		RTOrtnVel.msg)
	
# Declare the service files to be built
add_service_files(
	FILES
		BHandFingerPos.srv  BHandGraspVel.srv	CartPosMove.srv
		JointMove.srv
		BHandFingerVel.srv  BHandSpreadPos.srv	GravityComp.srv
		OrtnMove.srv
		BHandGraspPos.srv   BHandSpreadVel.srv	Hold.srv
		PoseMove.srv
)

# Actually generate the language-specific message and service files
generate_messages(DEPENDENCIES geometry_msgs)
# std_msgs sensor_msgs

# Declare that this catkin package's runtime dependencies
catkin_package(CATKIN_DEPENDS message_runtime)
# std_msgs sensor_msgs
