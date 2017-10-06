; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude BHandFingerVel-request.msg.html

(cl:defclass <BHandFingerVel-request> (roslisp-msg-protocol:ros-message)
  ((velocity
    :reader velocity
    :initarg :velocity
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass BHandFingerVel-request (<BHandFingerVel-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandFingerVel-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandFingerVel-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandFingerVel-request> is deprecated: use wam_srvs-srv:BHandFingerVel-request instead.")))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <BHandFingerVel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:velocity-val is deprecated.  Use wam_srvs-srv:velocity instead.")
  (velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandFingerVel-request>) ostream)
  "Serializes a message object of type '<BHandFingerVel-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'velocity))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandFingerVel-request>) istream)
  "Deserializes a message object of type '<BHandFingerVel-request>"
  (cl:setf (cl:slot-value msg 'velocity) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'velocity)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandFingerVel-request>)))
  "Returns string type for a service object of type '<BHandFingerVel-request>"
  "wam_srvs/BHandFingerVelRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandFingerVel-request)))
  "Returns string type for a service object of type 'BHandFingerVel-request"
  "wam_srvs/BHandFingerVelRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandFingerVel-request>)))
  "Returns md5sum for a message object of type '<BHandFingerVel-request>"
  "d4b1534f81253843d8e7435f97fbf189")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandFingerVel-request)))
  "Returns md5sum for a message object of type 'BHandFingerVel-request"
  "d4b1534f81253843d8e7435f97fbf189")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandFingerVel-request>)))
  "Returns full string definition for message of type '<BHandFingerVel-request>"
  (cl:format cl:nil "float32[3] velocity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandFingerVel-request)))
  "Returns full string definition for message of type 'BHandFingerVel-request"
  (cl:format cl:nil "float32[3] velocity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandFingerVel-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'velocity) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandFingerVel-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandFingerVel-request
    (cl:cons ':velocity (velocity msg))
))
;//! \htmlinclude BHandFingerVel-response.msg.html

(cl:defclass <BHandFingerVel-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass BHandFingerVel-response (<BHandFingerVel-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandFingerVel-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandFingerVel-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandFingerVel-response> is deprecated: use wam_srvs-srv:BHandFingerVel-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandFingerVel-response>) ostream)
  "Serializes a message object of type '<BHandFingerVel-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandFingerVel-response>) istream)
  "Deserializes a message object of type '<BHandFingerVel-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandFingerVel-response>)))
  "Returns string type for a service object of type '<BHandFingerVel-response>"
  "wam_srvs/BHandFingerVelResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandFingerVel-response)))
  "Returns string type for a service object of type 'BHandFingerVel-response"
  "wam_srvs/BHandFingerVelResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandFingerVel-response>)))
  "Returns md5sum for a message object of type '<BHandFingerVel-response>"
  "d4b1534f81253843d8e7435f97fbf189")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandFingerVel-response)))
  "Returns md5sum for a message object of type 'BHandFingerVel-response"
  "d4b1534f81253843d8e7435f97fbf189")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandFingerVel-response>)))
  "Returns full string definition for message of type '<BHandFingerVel-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandFingerVel-response)))
  "Returns full string definition for message of type 'BHandFingerVel-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandFingerVel-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandFingerVel-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandFingerVel-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BHandFingerVel)))
  'BHandFingerVel-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BHandFingerVel)))
  'BHandFingerVel-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandFingerVel)))
  "Returns string type for a service object of type '<BHandFingerVel>"
  "wam_srvs/BHandFingerVel")