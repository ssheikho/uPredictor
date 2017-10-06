; Auto-generated. Do not edit!


(cl:in-package wam_msgs-msg)


;//! \htmlinclude RTCartPos.msg.html

(cl:defclass <RTCartPos> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (rate_limits
    :reader rate_limits
    :initarg :rate_limits
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RTCartPos (<RTCartPos>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTCartPos>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTCartPos)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_msgs-msg:<RTCartPos> is deprecated: use wam_msgs-msg:RTCartPos instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <RTCartPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:position-val is deprecated.  Use wam_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'rate_limits-val :lambda-list '(m))
(cl:defmethod rate_limits-val ((m <RTCartPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:rate_limits-val is deprecated.  Use wam_msgs-msg:rate_limits instead.")
  (rate_limits m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTCartPos>) ostream)
  "Serializes a message object of type '<RTCartPos>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'position))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'rate_limits))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTCartPos>) istream)
  "Deserializes a message object of type '<RTCartPos>"
  (cl:setf (cl:slot-value msg 'position) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'position)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'rate_limits) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'rate_limits)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTCartPos>)))
  "Returns string type for a message object of type '<RTCartPos>"
  "wam_msgs/RTCartPos")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTCartPos)))
  "Returns string type for a message object of type 'RTCartPos"
  "wam_msgs/RTCartPos")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTCartPos>)))
  "Returns md5sum for a message object of type '<RTCartPos>"
  "f40423d4ca09896785d982c621cba554")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTCartPos)))
  "Returns md5sum for a message object of type 'RTCartPos"
  "f40423d4ca09896785d982c621cba554")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTCartPos>)))
  "Returns full string definition for message of type '<RTCartPos>"
  (cl:format cl:nil "float32[3] position~%float32[3] rate_limits~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTCartPos)))
  "Returns full string definition for message of type 'RTCartPos"
  (cl:format cl:nil "float32[3] position~%float32[3] rate_limits~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTCartPos>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'position) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'rate_limits) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTCartPos>))
  "Converts a ROS message object to a list"
  (cl:list 'RTCartPos
    (cl:cons ':position (position msg))
    (cl:cons ':rate_limits (rate_limits msg))
))
