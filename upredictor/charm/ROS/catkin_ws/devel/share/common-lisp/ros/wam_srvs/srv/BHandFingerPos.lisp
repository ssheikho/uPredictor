; Auto-generated. Do not edit!


(cl:in-package wam_srvs-srv)


;//! \htmlinclude BHandFingerPos-request.msg.html

(cl:defclass <BHandFingerPos-request> (roslisp-msg-protocol:ros-message)
  ((radians
    :reader radians
    :initarg :radians
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass BHandFingerPos-request (<BHandFingerPos-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandFingerPos-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandFingerPos-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandFingerPos-request> is deprecated: use wam_srvs-srv:BHandFingerPos-request instead.")))

(cl:ensure-generic-function 'radians-val :lambda-list '(m))
(cl:defmethod radians-val ((m <BHandFingerPos-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_srvs-srv:radians-val is deprecated.  Use wam_srvs-srv:radians instead.")
  (radians m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandFingerPos-request>) ostream)
  "Serializes a message object of type '<BHandFingerPos-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'radians))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandFingerPos-request>) istream)
  "Deserializes a message object of type '<BHandFingerPos-request>"
  (cl:setf (cl:slot-value msg 'radians) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'radians)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandFingerPos-request>)))
  "Returns string type for a service object of type '<BHandFingerPos-request>"
  "wam_srvs/BHandFingerPosRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandFingerPos-request)))
  "Returns string type for a service object of type 'BHandFingerPos-request"
  "wam_srvs/BHandFingerPosRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandFingerPos-request>)))
  "Returns md5sum for a message object of type '<BHandFingerPos-request>"
  "b8c122f38450d0302ba1a30c9c588995")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandFingerPos-request)))
  "Returns md5sum for a message object of type 'BHandFingerPos-request"
  "b8c122f38450d0302ba1a30c9c588995")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandFingerPos-request>)))
  "Returns full string definition for message of type '<BHandFingerPos-request>"
  (cl:format cl:nil "float32[3] radians~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandFingerPos-request)))
  "Returns full string definition for message of type 'BHandFingerPos-request"
  (cl:format cl:nil "float32[3] radians~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandFingerPos-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'radians) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandFingerPos-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandFingerPos-request
    (cl:cons ':radians (radians msg))
))
;//! \htmlinclude BHandFingerPos-response.msg.html

(cl:defclass <BHandFingerPos-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass BHandFingerPos-response (<BHandFingerPos-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BHandFingerPos-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BHandFingerPos-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_srvs-srv:<BHandFingerPos-response> is deprecated: use wam_srvs-srv:BHandFingerPos-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BHandFingerPos-response>) ostream)
  "Serializes a message object of type '<BHandFingerPos-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BHandFingerPos-response>) istream)
  "Deserializes a message object of type '<BHandFingerPos-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BHandFingerPos-response>)))
  "Returns string type for a service object of type '<BHandFingerPos-response>"
  "wam_srvs/BHandFingerPosResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandFingerPos-response)))
  "Returns string type for a service object of type 'BHandFingerPos-response"
  "wam_srvs/BHandFingerPosResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BHandFingerPos-response>)))
  "Returns md5sum for a message object of type '<BHandFingerPos-response>"
  "b8c122f38450d0302ba1a30c9c588995")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BHandFingerPos-response)))
  "Returns md5sum for a message object of type 'BHandFingerPos-response"
  "b8c122f38450d0302ba1a30c9c588995")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BHandFingerPos-response>)))
  "Returns full string definition for message of type '<BHandFingerPos-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BHandFingerPos-response)))
  "Returns full string definition for message of type 'BHandFingerPos-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BHandFingerPos-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BHandFingerPos-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BHandFingerPos-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BHandFingerPos)))
  'BHandFingerPos-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BHandFingerPos)))
  'BHandFingerPos-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BHandFingerPos)))
  "Returns string type for a service object of type '<BHandFingerPos>"
  "wam_srvs/BHandFingerPos")