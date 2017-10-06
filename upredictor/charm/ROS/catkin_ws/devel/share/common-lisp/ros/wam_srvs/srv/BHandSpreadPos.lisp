; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude BHandSpreadPos-request.msg.html

(cl:defclass <BHandSpreadPos-request> (roslisp-msg-protocol:ros-message)
  ((radians
    :reader radians
    :initarg :radians
    :type cl:float
    :initform 0.0))
)

(cl:defclass BHandSpreadPos-request (<BHandSpreadPos-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandSpreadPos-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandSpreadPos-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandSpreadPos-request> is deprecated: use wam_srvs-srv:BHandSpreadPos-request instead.")))

(cl:ensure-generic-function 'radians-val :lambda-list '(m))
(cl:defmethod radians-val ((m <BHandSpreadPos-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:radians-val is deprecated.  Use wam_srvs-srv:radians instead.")
  (radians m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandSpreadPos-request>) ostream)
  "Serializes a message object of type '<BHandSpreadPos-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radians))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandSpreadPos-request>) istream)
  "Deserializes a message object of type '<BHandSpreadPos-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radians) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandSpreadPos-request>)))
  "Returns string type for a service object of type '<BHandSpreadPos-request>"
  "wam_srvs/BHandSpreadPosRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandSpreadPos-request)))
  "Returns string type for a service object of type 'BHandSpreadPos-request"
  "wam_srvs/BHandSpreadPosRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandSpreadPos-request>)))
  "Returns md5sum for a message object of type '<BHandSpreadPos-request>"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandSpreadPos-request)))
  "Returns md5sum for a message object of type 'BHandSpreadPos-request"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandSpreadPos-request>)))
  "Returns full string definition for message of type '<BHandSpreadPos-request>"
  (cl:format cl:nil "float32 radians~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandSpreadPos-request)))
  "Returns full string definition for message of type 'BHandSpreadPos-request"
  (cl:format cl:nil "float32 radians~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandSpreadPos-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandSpreadPos-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandSpreadPos-request
    (cl:cons ':radians (radians msg))
))
;//! \htmlinclude BHandSpreadPos-response.msg.html

(cl:defclass <BHandSpreadPos-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass BHandSpreadPos-response (<BHandSpreadPos-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandSpreadPos-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandSpreadPos-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandSpreadPos-response> is deprecated: use wam_srvs-srv:BHandSpreadPos-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandSpreadPos-response>) ostream)
  "Serializes a message object of type '<BHandSpreadPos-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandSpreadPos-response>) istream)
  "Deserializes a message object of type '<BHandSpreadPos-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandSpreadPos-response>)))
  "Returns string type for a service object of type '<BHandSpreadPos-response>"
  "wam_srvs/BHandSpreadPosResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandSpreadPos-response)))
  "Returns string type for a service object of type 'BHandSpreadPos-response"
  "wam_srvs/BHandSpreadPosResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandSpreadPos-response>)))
  "Returns md5sum for a message object of type '<BHandSpreadPos-response>"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandSpreadPos-response)))
  "Returns md5sum for a message object of type 'BHandSpreadPos-response"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandSpreadPos-response>)))
  "Returns full string definition for message of type '<BHandSpreadPos-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandSpreadPos-response)))
  "Returns full string definition for message of type 'BHandSpreadPos-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandSpreadPos-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandSpreadPos-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandSpreadPos-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BHandSpreadPos)))
  'BHandSpreadPos-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BHandSpreadPos)))
  'BHandSpreadPos-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandSpreadPos)))
  "Returns string type for a service object of type '<BHandSpreadPos>"
  "wam_srvs/BHandSpreadPos")