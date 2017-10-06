; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude OrtnMove-request.msg.html

(cl:defclass <OrtnMove-request> (roslisp-msg-protocol:ros-message)
  ((orientation
    :reader orientation
    :initarg :orientation
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass OrtnMove-request (<OrtnMove-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OrtnMove-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OrtnMove-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<OrtnMove-request> is deprecated: use wam_srvs-srv:OrtnMove-request instead.")))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <OrtnMove-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:orientation-val is deprecated.  Use wam_srvs-srv:orientation instead.")
  (orientation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OrtnMove-request>) ostream)
  "Serializes a message object of type '<OrtnMove-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'orientation))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OrtnMove-request>) istream)
  "Deserializes a message object of type '<OrtnMove-request>"
  (cl:setf (cl:slot-value msg 'orientation) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'orientation)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OrtnMove-request>)))
  "Returns string type for a service object of type '<OrtnMove-request>"
  "wam_srvs/OrtnMoveRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OrtnMove-request)))
  "Returns string type for a service object of type 'OrtnMove-request"
  "wam_srvs/OrtnMoveRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OrtnMove-request>)))
  "Returns md5sum for a message object of type '<OrtnMove-request>"
  "86f723fe9a4be8979be87cd065276584")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OrtnMove-request)))
  "Returns md5sum for a message object of type 'OrtnMove-request"
  "86f723fe9a4be8979be87cd065276584")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OrtnMove-request>)))
  "Returns full string definition for message of type '<OrtnMove-request>"
  (cl:format cl:nil "float32[4] orientation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OrtnMove-request)))
  "Returns full string definition for message of type 'OrtnMove-request"
  (cl:format cl:nil "float32[4] orientation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OrtnMove-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'orientation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OrtnMove-request>))
  "Converts a ROS message object to a list"
  (cl:list 'OrtnMove-request
    (cl:cons ':orientation (orientation msg))
))
;//! \htmlinclude OrtnMove-response.msg.html

(cl:defclass <OrtnMove-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass OrtnMove-response (<OrtnMove-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OrtnMove-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OrtnMove-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<OrtnMove-response> is deprecated: use wam_srvs-srv:OrtnMove-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OrtnMove-response>) ostream)
  "Serializes a message object of type '<OrtnMove-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OrtnMove-response>) istream)
  "Deserializes a message object of type '<OrtnMove-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OrtnMove-response>)))
  "Returns string type for a service object of type '<OrtnMove-response>"
  "wam_srvs/OrtnMoveResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OrtnMove-response)))
  "Returns string type for a service object of type 'OrtnMove-response"
  "wam_srvs/OrtnMoveResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OrtnMove-response>)))
  "Returns md5sum for a message object of type '<OrtnMove-response>"
  "86f723fe9a4be8979be87cd065276584")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OrtnMove-response)))
  "Returns md5sum for a message object of type 'OrtnMove-response"
  "86f723fe9a4be8979be87cd065276584")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OrtnMove-response>)))
  "Returns full string definition for message of type '<OrtnMove-response>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OrtnMove-response)))
  "Returns full string definition for message of type 'OrtnMove-response"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OrtnMove-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OrtnMove-response>))
  "Converts a ROS message object to a list"
  (cl:list 'OrtnMove-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'OrtnMove)))
  'OrtnMove-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'OrtnMove)))
  'OrtnMove-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OrtnMove)))
  "Returns string type for a service object of type '<OrtnMove>"
  "wam_srvs/OrtnMove")