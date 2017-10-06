#!/usr/bin/env python
import rospy
from control_msgs.msg import JointTrajectoryControllerState
from sensor_msgs.msg import JointState

def cb(data):
    joint_names = data.joint_names
    desired = data.desired

    msg = JointState()
    msg.name = joint_names
    msg.position = desired.positions
    msg.velocity = desired.velocities

    global pub
    pub.publish(msg)

def remap():
    rospy.init_node('joint_state_publisher_remap', anonymous=True)
    
    arm_sub = rospy.Subscriber('/wam/arm_trajectory_controller/state', JointTrajectoryControllerState, cb)
    hand_sub = rospy.Subscriber('/wam/hand_trajectory_controller/state', JointTrajectoryControllerState, cb)
    
    global pub
    pub = rospy.Publisher('joint_states', JointState, queue_size=10)
    rospy.spin()

if __name__ == '__main__':
    remap()