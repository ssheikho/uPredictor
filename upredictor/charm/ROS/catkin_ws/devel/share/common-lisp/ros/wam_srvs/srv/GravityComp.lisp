; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude GravityComp-request.msg.html

(cl:defclass <GravityComp-request> (roslisp-msg-protocol:ros-message)
  ((gravity
    :reader gravity
    :initarg :gravity
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GravityComp-request (<GravityComp-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GravityComp-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GravityComp-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<GravityComp-request> is deprecated: use wam_srvs-srv:GravityComp-request instead.")))

(cl:ensure-generic-function 'gravity-val :lambda-list '(m))
(cl:defmethod gravity-val ((m <GravityComp-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:gravity-val is deprecated.  Use wam_srvs-srv:gravity instead.")
  (gravity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GravityComp-request>) ostream)
  "Serializes a message object of type '<GravityComp-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'gravity) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GravityComp-request>) istream)
  "Deserializes a message object of type '<GravityComp-request>"
    (cl:setf (cl:slot-value msg 'gravity) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GravityComp-request>)))
  "Returns string type for a service object of type '<GravityComp-request>"
  "wam_srvs/GravityCompRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GravityComp-request)))
  "Returns string type for a service object of type 'GravityComp-request"
  "wam_srvs/GravityCompRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GravityComp-request>)))
  "Returns md5sum for a message object of type '<GravityComp-request>"
  "f83a9fe078fab9865d863fbf215e1c14")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GravityComp-request)))
  "Returns md5sum for a message object of type 'GravityComp-request"
  "f83a9fe078fab9865d863fbf215e1c14")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GravityComp-request>)))
  "Returns full string definition for message of type '<GravityComp-request>"
  (cl:format cl:nil "bool gravity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GravityComp-request)))
  "Returns full string definition for message of type 'GravityComp-request"
  (cl:format cl:nil "bool gravity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GravityComp-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GravityComp-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GravityComp-request
    (cl:cons ':gravity (gravity msg))
))
;//! \htmlinclude GravityComp-response.msg.html

(cl:defclass <GravityComp-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GravityComp-response (<GravityComp-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GravityComp-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GravityComp-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<GravityComp-response> is deprecated: use wam_srvs-srv:GravityComp-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GravityComp-response>) ostream)
  "Serializes a message object of type '<GravityComp-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GravityComp-response>) istream)
  "Deserializes a message object of type '<GravityComp-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GravityComp-response>)))
  "Returns string type for a service object of type '<GravityComp-response>"
  "wam_srvs/GravityCompResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GravityComp-response)))
  "Returns string type for a service object of type 'GravityComp-response"
  "wam_srvs/GravityCompResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GravityComp-response>)))
  "Returns md5sum for a message object of type '<GravityComp-response>"
  "f83a9fe078fab9865d863fbf215e1c14")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GravityComp-response)))
  "Returns md5sum for a message object of type 'GravityComp-response"
  "f83a9fe078fab9865d863fbf215e1c14")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GravityComp-response>)))
  "Returns full string definition for message of type '<GravityComp-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GravityComp-response)))
  "Returns full string definition for message of type 'GravityComp-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GravityComp-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GravityComp-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GravityComp-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GravityComp)))
  'GravityComp-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GravityComp)))
  'GravityComp-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GravityComp)))
  "Returns string type for a service object of type '<GravityComp>"
  "wam_srvs/GravityComp")