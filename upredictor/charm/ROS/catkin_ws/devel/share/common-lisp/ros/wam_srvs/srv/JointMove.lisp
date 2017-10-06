; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude JointMove-request.msg.html

(cl:defclass <JointMove-request> (roslisp-msg-protocol:ros-message)
  ((joints
    :reader joints
    :initarg :joints
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass JointMove-request (<JointMove-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointMove-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointMove-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<JointMove-request> is deprecated: use wam_srvs-srv:JointMove-request instead.")))

(cl:ensure-generic-function 'joints-val :lambda-list '(m))
(cl:defmethod joints-val ((m <JointMove-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:joints-val is deprecated.  Use wam_srvs-srv:joints instead.")
  (joints m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointMove-request>) ostream)
  "Serializes a message object of type '<JointMove-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'joints))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'joints))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointMove-request>) istream)
  "Deserializes a message object of type '<JointMove-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'joints) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'joints)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointMove-request>)))
  "Returns string type for a service object of type '<JointMove-request>"
  "wam_srvs/JointMoveRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointMove-request)))
  "Returns string type for a service object of type 'JointMove-request"
  "wam_srvs/JointMoveRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointMove-request>)))
  "Returns md5sum for a message object of type '<JointMove-request>"
  "e2a0e438b445b98def0f0ba6a2a85f58")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointMove-request)))
  "Returns md5sum for a message object of type 'JointMove-request"
  "e2a0e438b445b98def0f0ba6a2a85f58")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointMove-request>)))
  "Returns full string definition for message of type '<JointMove-request>"
  (cl:format cl:nil "float32[] joints~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointMove-request)))
  "Returns full string definition for message of type 'JointMove-request"
  (cl:format cl:nil "float32[] joints~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointMove-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'joints) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointMove-request>))
  "Converts a ROS message object to a list"
  (cl:list 'JointMove-request
    (cl:cons ':joints (joints msg))
))
;//! \htmlinclude JointMove-response.msg.html

(cl:defclass <JointMove-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass JointMove-response (<JointMove-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointMove-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointMove-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<JointMove-response> is deprecated: use wam_srvs-srv:JointMove-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointMove-response>) ostream)
  "Serializes a message object of type '<JointMove-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointMove-response>) istream)
  "Deserializes a message object of type '<JointMove-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointMove-response>)))
  "Returns string type for a service object of type '<JointMove-response>"
  "wam_srvs/JointMoveResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointMove-response)))
  "Returns string type for a service object of type 'JointMove-response"
  "wam_srvs/JointMoveResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointMove-response>)))
  "Returns md5sum for a message object of type '<JointMove-response>"
  "e2a0e438b445b98def0f0ba6a2a85f58")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointMove-response)))
  "Returns md5sum for a message object of type 'JointMove-response"
  "e2a0e438b445b98def0f0ba6a2a85f58")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointMove-response>)))
  "Returns full string definition for message of type '<JointMove-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointMove-response)))
  "Returns full string definition for message of type 'JointMove-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointMove-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointMove-response>))
  "Converts a ROS message object to a list"
  (cl:list 'JointMove-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'JointMove)))
  'JointMove-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'JointMove)))
  'JointMove-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointMove)))
  "Returns string type for a service object of type '<JointMove>"
  "wam_srvs/JointMove")