; Auto-generated. Do not edit!


(cl:in-package wam_msgs-msg)


;//! \htmlinclude RTOrtnPos.msg.html

(cl:defclass <RTOrtnPos> (roslisp-msg-protocol:ros-message)
  ((orientation
    :reader orientation
    :initarg :orientation
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0))
   (rate_limits
    :reader rate_limits
    :initarg :rate_limits
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RTOrtnPos (<RTOrtnPos>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTOrtnPos>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTOrtnPos)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_msgs-msg:<RTOrtnPos> is deprecated: use wam_msgs-msg:RTOrtnPos instead.")))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <RTOrtnPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:orientation-val is deprecated.  Use wam_msgs-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'rate_limits-val :lambda-list '(m))
(cl:defmethod rate_limits-val ((m <RTOrtnPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:rate_limits-val is deprecated.  Use wam_msgs-msg:rate_limits instead.")
  (rate_limits m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTOrtnPos>) ostream)
  "Serializes a message object of type '<RTOrtnPos>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'orientation))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'rate_limits))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTOrtnPos>) istream)
  "Deserializes a message object of type '<RTOrtnPos>"
  (cl:setf (cl:slot-value msg 'orientation) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'orientation)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'rate_limits) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'rate_limits)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTOrtnPos>)))
  "Returns string type for a message object of type '<RTOrtnPos>"
  "wam_msgs/RTOrtnPos")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTOrtnPos)))
  "Returns string type for a message object of type 'RTOrtnPos"
  "wam_msgs/RTOrtnPos")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTOrtnPos>)))
  "Returns md5sum for a message object of type '<RTOrtnPos>"
  "5b352081db430205c87e0e439f09a0b2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTOrtnPos)))
  "Returns md5sum for a message object of type 'RTOrtnPos"
  "5b352081db430205c87e0e439f09a0b2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTOrtnPos>)))
  "Returns full string definition for message of type '<RTOrtnPos>"
  (cl:format cl:nil "float32[4] orientation~%float32[4] rate_limits~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTOrtnPos)))
  "Returns full string definition for message of type 'RTOrtnPos"
  (cl:format cl:nil "float32[4] orientation~%float32[4] rate_limits~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTOrtnPos>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'orientation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'rate_limits) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTOrtnPos>))
  "Converts a ROS message object to a list"
  (cl:list 'RTOrtnPos
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':rate_limits (rate_limits msg))
))
