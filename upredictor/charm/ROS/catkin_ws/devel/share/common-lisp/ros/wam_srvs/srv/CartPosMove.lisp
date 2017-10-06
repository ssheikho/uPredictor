; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude CartPosMove-request.msg.html

(cl:defclass <CartPosMove-request> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass CartPosMove-request (<CartPosMove-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CartPosMove-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CartPosMove-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<CartPosMove-request> is deprecated: use wam_srvs-srv:CartPosMove-request instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <CartPosMove-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:position-val is deprecated.  Use wam_srvs-srv:position instead.")
  (position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CartPosMove-request>) ostream)
  "Serializes a message object of type '<CartPosMove-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'position))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CartPosMove-request>) istream)
  "Deserializes a message object of type '<CartPosMove-request>"
  (cl:setf (cl:slot-value msg 'position) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'position)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CartPosMove-request>)))
  "Returns string type for a service object of type '<CartPosMove-request>"
  "wam_srvs/CartPosMoveRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CartPosMove-request)))
  "Returns string type for a service object of type 'CartPosMove-request"
  "wam_srvs/CartPosMoveRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CartPosMove-request>)))
  "Returns md5sum for a message object of type '<CartPosMove-request>"
  "993d3a0cca92114d34b338aeb1007ee4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CartPosMove-request)))
  "Returns md5sum for a message object of type 'CartPosMove-request"
  "993d3a0cca92114d34b338aeb1007ee4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CartPosMove-request>)))
  "Returns full string definition for message of type '<CartPosMove-request>"
  (cl:format cl:nil "float32[3] position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CartPosMove-request)))
  "Returns full string definition for message of type 'CartPosMove-request"
  (cl:format cl:nil "float32[3] position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CartPosMove-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'position) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CartPosMove-request>))
  "Converts a ROS message object to a list"
  (cl:list 'CartPosMove-request
    (cl:cons ':position (position msg))
))
;//! \htmlinclude CartPosMove-response.msg.html

(cl:defclass <CartPosMove-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass CartPosMove-response (<CartPosMove-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CartPosMove-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CartPosMove-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<CartPosMove-response> is deprecated: use wam_srvs-srv:CartPosMove-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CartPosMove-response>) ostream)
  "Serializes a message object of type '<CartPosMove-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CartPosMove-response>) istream)
  "Deserializes a message object of type '<CartPosMove-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CartPosMove-response>)))
  "Returns string type for a service object of type '<CartPosMove-response>"
  "wam_srvs/CartPosMoveResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CartPosMove-response)))
  "Returns string type for a service object of type 'CartPosMove-response"
  "wam_srvs/CartPosMoveResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CartPosMove-response>)))
  "Returns md5sum for a message object of type '<CartPosMove-response>"
  "993d3a0cca92114d34b338aeb1007ee4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CartPosMove-response)))
  "Returns md5sum for a message object of type 'CartPosMove-response"
  "993d3a0cca92114d34b338aeb1007ee4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CartPosMove-response>)))
  "Returns full string definition for message of type '<CartPosMove-response>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CartPosMove-response)))
  "Returns full string definition for message of type 'CartPosMove-response"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CartPosMove-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CartPosMove-response>))
  "Converts a ROS message object to a list"
  (cl:list 'CartPosMove-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'CartPosMove)))
  'CartPosMove-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'CartPosMove)))
  'CartPosMove-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CartPosMove)))
  "Returns string type for a service object of type '<CartPosMove>"
  "wam_srvs/CartPosMove")