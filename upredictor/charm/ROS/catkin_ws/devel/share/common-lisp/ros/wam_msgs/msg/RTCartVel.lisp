; Auto-generated. Do not edit!


(cl:in-package wam_msgs-msg)


;//! \htmlinclude RTCartVel.msg.html

(cl:defclass <RTCartVel> (roslisp-msg-protocol:ros-message)
  ((direction
    :reader direction
    :initarg :direction
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (magnitude
    :reader magnitude
    :initarg :magnitude
    :type cl:float
    :initform 0.0))
)

(cl:defclass RTCartVel (<RTCartVel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTCartVel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTCartVel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_msgs-msg:<RTCartVel> is deprecated: use wam_msgs-msg:RTCartVel instead.")))

(cl:ensure-generic-function 'direction-val :lambda-list '(m))
(cl:defmethod direction-val ((m <RTCartVel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:direction-val is deprecated.  Use wam_msgs-msg:direction instead.")
  (direction m))

(cl:ensure-generic-function 'magnitude-val :lambda-list '(m))
(cl:defmethod magnitude-val ((m <RTCartVel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:magnitude-val is deprecated.  Use wam_msgs-msg:magnitude instead.")
  (magnitude m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTCartVel>) ostream)
  "Serializes a message object of type '<RTCartVel>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'direction))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'magnitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTCartVel>) istream)
  "Deserializes a message object of type '<RTCartVel>"
  (cl:setf (cl:slot-value msg 'direction) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'direction)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'magnitude) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTCartVel>)))
  "Returns string type for a message object of type '<RTCartVel>"
  "wam_msgs/RTCartVel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTCartVel)))
  "Returns string type for a message object of type 'RTCartVel"
  "wam_msgs/RTCartVel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTCartVel>)))
  "Returns md5sum for a message object of type '<RTCartVel>"
  "bde6e49ce1902bc915138d25af0e9ef1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTCartVel)))
  "Returns md5sum for a message object of type 'RTCartVel"
  "bde6e49ce1902bc915138d25af0e9ef1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTCartVel>)))
  "Returns full string definition for message of type '<RTCartVel>"
  (cl:format cl:nil "float32[3] direction~%float32    magnitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTCartVel)))
  "Returns full string definition for message of type 'RTCartVel"
  (cl:format cl:nil "float32[3] direction~%float32    magnitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTCartVel>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'direction) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTCartVel>))
  "Converts a ROS message object to a list"
  (cl:list 'RTCartVel
    (cl:cons ':direction (direction msg))
    (cl:cons ':magnitude (magnitude msg))
))
