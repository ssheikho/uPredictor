; Auto-generated. Do not edit!


(cl:in-package wam_msgs-msg)


;//! \htmlinclude RTJointVel.msg.html

(cl:defclass <RTJointVel> (roslisp-msg-protocol:ros-message)
  ((velocities
    :reader velocities
    :initarg :velocities
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RTJointVel (<RTJointVel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTJointVel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTJointVel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_msgs-msg:<RTJointVel> is deprecated: use wam_msgs-msg:RTJointVel instead.")))

(cl:ensure-generic-function 'velocities-val :lambda-list '(m))
(cl:defmethod velocities-val ((m <RTJointVel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:velocities-val is deprecated.  Use wam_msgs-msg:velocities instead.")
  (velocities m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTJointVel>) ostream)
  "Serializes a message object of type '<RTJointVel>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'velocities))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'velocities))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTJointVel>) istream)
  "Deserializes a message object of type '<RTJointVel>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'velocities) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'velocities)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTJointVel>)))
  "Returns string type for a message object of type '<RTJointVel>"
  "wam_msgs/RTJointVel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTJointVel)))
  "Returns string type for a message object of type 'RTJointVel"
  "wam_msgs/RTJointVel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTJointVel>)))
  "Returns md5sum for a message object of type '<RTJointVel>"
  "9b1dee67c9ae4d5adf87be09d4bf02ef")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTJointVel)))
  "Returns md5sum for a message object of type 'RTJointVel"
  "9b1dee67c9ae4d5adf87be09d4bf02ef")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTJointVel>)))
  "Returns full string definition for message of type '<RTJointVel>"
  (cl:format cl:nil "float32[] velocities~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTJointVel)))
  "Returns full string definition for message of type 'RTJointVel"
  (cl:format cl:nil "float32[] velocities~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTJointVel>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'velocities) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTJointVel>))
  "Converts a ROS message object to a list"
  (cl:list 'RTJointVel
    (cl:cons ':velocities (velocities msg))
))
