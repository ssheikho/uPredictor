; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude BHandSpreadVel-request.msg.html

(cl:defclass <BHandSpreadVel-request> (roslisp-msg-protocol:ros-message)
  ((velocity
    :reader velocity
    :initarg :velocity
    :type cl:float
    :initform 0.0))
)

(cl:defclass BHandSpreadVel-request (<BHandSpreadVel-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandSpreadVel-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandSpreadVel-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandSpreadVel-request> is deprecated: use wam_srvs-srv:BHandSpreadVel-request instead.")))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <BHandSpreadVel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:velocity-val is deprecated.  Use wam_srvs-srv:velocity instead.")
  (velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandSpreadVel-request>) ostream)
  "Serializes a message object of type '<BHandSpreadVel-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandSpreadVel-request>) istream)
  "Deserializes a message object of type '<BHandSpreadVel-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandSpreadVel-request>)))
  "Returns string type for a service object of type '<BHandSpreadVel-request>"
  "wam_srvs/BHandSpreadVelRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandSpreadVel-request)))
  "Returns string type for a service object of type 'BHandSpreadVel-request"
  "wam_srvs/BHandSpreadVelRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandSpreadVel-request>)))
  "Returns md5sum for a message object of type '<BHandSpreadVel-request>"
  "e4ff88b32504f688719a85e0753f63ce")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandSpreadVel-request)))
  "Returns md5sum for a message object of type 'BHandSpreadVel-request"
  "e4ff88b32504f688719a85e0753f63ce")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandSpreadVel-request>)))
  "Returns full string definition for message of type '<BHandSpreadVel-request>"
  (cl:format cl:nil "float32 velocity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandSpreadVel-request)))
  "Returns full string definition for message of type 'BHandSpreadVel-request"
  (cl:format cl:nil "float32 velocity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandSpreadVel-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandSpreadVel-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandSpreadVel-request
    (cl:cons ':velocity (velocity msg))
))
;//! \htmlinclude BHandSpreadVel-response.msg.html

(cl:defclass <BHandSpreadVel-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass BHandSpreadVel-response (<BHandSpreadVel-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandSpreadVel-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandSpreadVel-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandSpreadVel-response> is deprecated: use wam_srvs-srv:BHandSpreadVel-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandSpreadVel-response>) ostream)
  "Serializes a message object of type '<BHandSpreadVel-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandSpreadVel-response>) istream)
  "Deserializes a message object of type '<BHandSpreadVel-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandSpreadVel-response>)))
  "Returns string type for a service object of type '<BHandSpreadVel-response>"
  "wam_srvs/BHandSpreadVelResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandSpreadVel-response)))
  "Returns string type for a service object of type 'BHandSpreadVel-response"
  "wam_srvs/BHandSpreadVelResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandSpreadVel-response>)))
  "Returns md5sum for a message object of type '<BHandSpreadVel-response>"
  "e4ff88b32504f688719a85e0753f63ce")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandSpreadVel-response)))
  "Returns md5sum for a message object of type 'BHandSpreadVel-response"
  "e4ff88b32504f688719a85e0753f63ce")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandSpreadVel-response>)))
  "Returns full string definition for message of type '<BHandSpreadVel-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandSpreadVel-response)))
  "Returns full string definition for message of type 'BHandSpreadVel-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandSpreadVel-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandSpreadVel-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandSpreadVel-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BHandSpreadVel)))
  'BHandSpreadVel-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BHandSpreadVel)))
  'BHandSpreadVel-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandSpreadVel)))
  "Returns string type for a service object of type '<BHandSpreadVel>"
  "wam_srvs/BHandSpreadVel")