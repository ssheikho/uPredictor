; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude BHandGraspPos-request.msg.html

(cl:defclass <BHandGraspPos-request> (roslisp-msg-protocol:ros-message)
  ((radians
    :reader radians
    :initarg :radians
    :type cl:float
    :initform 0.0))
)

(cl:defclass BHandGraspPos-request (<BHandGraspPos-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandGraspPos-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandGraspPos-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandGraspPos-request> is deprecated: use wam_srvs-srv:BHandGraspPos-request instead.")))

(cl:ensure-generic-function 'radians-val :lambda-list '(m))
(cl:defmethod radians-val ((m <BHandGraspPos-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:radians-val is deprecated.  Use wam_srvs-srv:radians instead.")
  (radians m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandGraspPos-request>) ostream)
  "Serializes a message object of type '<BHandGraspPos-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radians))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandGraspPos-request>) istream)
  "Deserializes a message object of type '<BHandGraspPos-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radians) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandGraspPos-request>)))
  "Returns string type for a service object of type '<BHandGraspPos-request>"
  "wam_srvs/BHandGraspPosRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandGraspPos-request)))
  "Returns string type for a service object of type 'BHandGraspPos-request"
  "wam_srvs/BHandGraspPosRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandGraspPos-request>)))
  "Returns md5sum for a message object of type '<BHandGraspPos-request>"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandGraspPos-request)))
  "Returns md5sum for a message object of type 'BHandGraspPos-request"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandGraspPos-request>)))
  "Returns full string definition for message of type '<BHandGraspPos-request>"
  (cl:format cl:nil "float32 radians~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandGraspPos-request)))
  "Returns full string definition for message of type 'BHandGraspPos-request"
  (cl:format cl:nil "float32 radians~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandGraspPos-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandGraspPos-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandGraspPos-request
    (cl:cons ':radians (radians msg))
))
;//! \htmlinclude BHandGraspPos-response.msg.html

(cl:defclass <BHandGraspPos-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass BHandGraspPos-response (<BHandGraspPos-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandGraspPos-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandGraspPos-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandGraspPos-response> is deprecated: use wam_srvs-srv:BHandGraspPos-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandGraspPos-response>) ostream)
  "Serializes a message object of type '<BHandGraspPos-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandGraspPos-response>) istream)
  "Deserializes a message object of type '<BHandGraspPos-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandGraspPos-response>)))
  "Returns string type for a service object of type '<BHandGraspPos-response>"
  "wam_srvs/BHandGraspPosResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandGraspPos-response)))
  "Returns string type for a service object of type 'BHandGraspPos-response"
  "wam_srvs/BHandGraspPosResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandGraspPos-response>)))
  "Returns md5sum for a message object of type '<BHandGraspPos-response>"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandGraspPos-response)))
  "Returns md5sum for a message object of type 'BHandGraspPos-response"
  "718158cfca4f89c6952f799c53697f42")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandGraspPos-response>)))
  "Returns full string definition for message of type '<BHandGraspPos-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandGraspPos-response)))
  "Returns full string definition for message of type 'BHandGraspPos-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandGraspPos-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandGraspPos-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandGraspPos-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BHandGraspPos)))
  'BHandGraspPos-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BHandGraspPos)))
  'BHandGraspPos-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandGraspPos)))
  "Returns string type for a service object of type '<BHandGraspPos>"
  "wam_srvs/BHandGraspPos")