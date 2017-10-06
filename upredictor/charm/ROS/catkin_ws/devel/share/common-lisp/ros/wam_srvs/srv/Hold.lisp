; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude Hold-request.msg.html

(cl:defclass <Hold-request> (roslisp-msg-protocol:ros-message)
  ((hold
    :reader hold
    :initarg :hold
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Hold-request (<Hold-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Hold-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Hold-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<Hold-request> is deprecated: use wam_srvs-srv:Hold-request instead.")))

(cl:ensure-generic-function 'hold-val :lambda-list '(m))
(cl:defmethod hold-val ((m <Hold-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:hold-val is deprecated.  Use wam_srvs-srv:hold instead.")
  (hold m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Hold-request>) ostream)
  "Serializes a message object of type '<Hold-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'hold) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Hold-request>) istream)
  "Deserializes a message object of type '<Hold-request>"
    (cl:setf (cl:slot-value msg 'hold) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Hold-request>)))
  "Returns string type for a service object of type '<Hold-request>"
  "wam_srvs/HoldRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Hold-request)))
  "Returns string type for a service object of type 'Hold-request"
  "wam_srvs/HoldRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Hold-request>)))
  "Returns md5sum for a message object of type '<Hold-request>"
  "797a139a4299aebd587b00a7001c67f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Hold-request)))
  "Returns md5sum for a message object of type 'Hold-request"
  "797a139a4299aebd587b00a7001c67f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Hold-request>)))
  "Returns full string definition for message of type '<Hold-request>"
  (cl:format cl:nil "bool hold~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Hold-request)))
  "Returns full string definition for message of type 'Hold-request"
  (cl:format cl:nil "bool hold~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Hold-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Hold-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Hold-request
    (cl:cons ':hold (hold msg))
))
;//! \htmlinclude Hold-response.msg.html

(cl:defclass <Hold-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass Hold-response (<Hold-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Hold-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Hold-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<Hold-response> is deprecated: use wam_srvs-srv:Hold-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Hold-response>) ostream)
  "Serializes a message object of type '<Hold-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Hold-response>) istream)
  "Deserializes a message object of type '<Hold-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Hold-response>)))
  "Returns string type for a service object of type '<Hold-response>"
  "wam_srvs/HoldResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Hold-response)))
  "Returns string type for a service object of type 'Hold-response"
  "wam_srvs/HoldResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Hold-response>)))
  "Returns md5sum for a message object of type '<Hold-response>"
  "797a139a4299aebd587b00a7001c67f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Hold-response)))
  "Returns md5sum for a message object of type 'Hold-response"
  "797a139a4299aebd587b00a7001c67f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Hold-response>)))
  "Returns full string definition for message of type '<Hold-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Hold-response)))
  "Returns full string definition for message of type 'Hold-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Hold-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Hold-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Hold-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Hold)))
  'Hold-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Hold)))
  'Hold-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Hold)))
  "Returns string type for a service object of type '<Hold>"
  "wam_srvs/Hold")