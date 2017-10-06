; Auto-generated. Do not edit!


(cl:in-package wam_msgs-msg)


;//! \htmlinclude RTOrtnVel.msg.html

(cl:defclass <RTOrtnVel> (roslisp-msg-protocol:ros-message)
  ((angular
    :reader angular
    :initarg :angular
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (magnitude
    :reader magnitude
    :initarg :magnitude
    :type cl:float
    :initform 0.0))
)

(cl:defclass RTOrtnVel (<RTOrtnVel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTOrtnVel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTOrtnVel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_msgs-msg:<RTOrtnVel> is deprecated: use wam_msgs-msg:RTOrtnVel instead.")))

(cl:ensure-generic-function 'angular-val :lambda-list '(m))
(cl:defmethod angular-val ((m <RTOrtnVel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:angular-val is deprecated.  Use wam_msgs-msg:angular instead.")
  (angular m))

(cl:ensure-generic-function 'magnitude-val :lambda-list '(m))
(cl:defmethod magnitude-val ((m <RTOrtnVel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:magnitude-val is deprecated.  Use wam_msgs-msg:magnitude instead.")
  (magnitude m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTOrtnVel>) ostream)
  "Serializes a message object of type '<RTOrtnVel>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'angular))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'magnitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTOrtnVel>) istream)
  "Deserializes a message object of type '<RTOrtnVel>"
  (cl:setf (cl:slot-value msg 'angular) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'angular)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTOrtnVel>)))
  "Returns string type for a message object of type '<RTOrtnVel>"
  "wam_msgs/RTOrtnVel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTOrtnVel)))
  "Returns string type for a message object of type 'RTOrtnVel"
  "wam_msgs/RTOrtnVel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTOrtnVel>)))
  "Returns md5sum for a message object of type '<RTOrtnVel>"
  "2326f85574083a0a1fc4fddeff59781c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTOrtnVel)))
  "Returns md5sum for a message object of type 'RTOrtnVel"
  "2326f85574083a0a1fc4fddeff59781c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTOrtnVel>)))
  "Returns full string definition for message of type '<RTOrtnVel>"
  (cl:format cl:nil "float32[3] angular~%float32	   magnitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTOrtnVel)))
  "Returns full string definition for message of type 'RTOrtnVel"
  (cl:format cl:nil "float32[3] angular~%float32	   magnitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTOrtnVel>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angular) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTOrtnVel>))
  "Converts a ROS message object to a list"
  (cl:list 'RTOrtnVel
    (cl:cons ':angular (angular msg))
    (cl:cons ':magnitude (magnitude msg))
))
