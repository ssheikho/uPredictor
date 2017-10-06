; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude PoseMove-request.msg.html

(cl:defclass <PoseMove-request> (roslisp-msg-protocol:ros-message)
  ((pose
    :reader pose
    :initarg :pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass PoseMove-request (<PoseMove-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseMove-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseMove-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<PoseMove-request> is deprecated: use wam_srvs-srv:PoseMove-request instead.")))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <PoseMove-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:pose-val is deprecated.  Use wam_srvs-srv:pose instead.")
  (pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseMove-request>) ostream)
  "Serializes a message object of type '<PoseMove-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseMove-request>) istream)
  "Deserializes a message object of type '<PoseMove-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseMove-request>)))
  "Returns string type for a service object of type '<PoseMove-request>"
  "wam_srvs/PoseMoveRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseMove-request)))
  "Returns string type for a service object of type 'PoseMove-request"
  "wam_srvs/PoseMoveRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseMove-request>)))
  "Returns md5sum for a message object of type '<PoseMove-request>"
  "f192399f711a48924df9a394d37edd67")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseMove-request)))
  "Returns md5sum for a message object of type 'PoseMove-request"
  "f192399f711a48924df9a394d37edd67")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseMove-request>)))
  "Returns full string definition for message of type '<PoseMove-request>"
  (cl:format cl:nil "geometry_msgs/Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseMove-request)))
  "Returns full string definition for message of type 'PoseMove-request"
  (cl:format cl:nil "geometry_msgs/Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseMove-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseMove-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseMove-request
    (cl:cons ':pose (pose msg))
))
;//! \htmlinclude PoseMove-response.msg.html

(cl:defclass <PoseMove-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass PoseMove-response (<PoseMove-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseMove-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseMove-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<PoseMove-response> is deprecated: use wam_srvs-srv:PoseMove-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseMove-response>) ostream)
  "Serializes a message object of type '<PoseMove-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseMove-response>) istream)
  "Deserializes a message object of type '<PoseMove-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseMove-response>)))
  "Returns string type for a service object of type '<PoseMove-response>"
  "wam_srvs/PoseMoveResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseMove-response)))
  "Returns string type for a service object of type 'PoseMove-response"
  "wam_srvs/PoseMoveResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseMove-response>)))
  "Returns md5sum for a message object of type '<PoseMove-response>"
  "f192399f711a48924df9a394d37edd67")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseMove-response)))
  "Returns md5sum for a message object of type 'PoseMove-response"
  "f192399f711a48924df9a394d37edd67")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseMove-response>)))
  "Returns full string definition for message of type '<PoseMove-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseMove-response)))
  "Returns full string definition for message of type 'PoseMove-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseMove-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseMove-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseMove-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PoseMove)))
  'PoseMove-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PoseMove)))
  'PoseMove-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseMove)))
  "Returns string type for a service object of type '<PoseMove>"
  "wam_srvs/PoseMove")