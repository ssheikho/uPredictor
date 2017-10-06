; Auto-generated. Do not edit!


(cl:in-package wam_msgs-msg)


;//! \htmlinclude RTPose.msg.html

(cl:defclass <RTPose> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (orientation
    :reader orientation
    :initarg :orientation
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0))
   (pos_rate_limits
    :reader pos_rate_limits
    :initarg :pos_rate_limits
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (ortn_rate_limits
    :reader ortn_rate_limits
    :initarg :ortn_rate_limits
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RTPose (<RTPose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTPose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTPose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name wam_msgs-msg:<RTPose> is deprecated: use wam_msgs-msg:RTPose instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <RTPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:position-val is deprecated.  Use wam_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <RTPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:orientation-val is deprecated.  Use wam_msgs-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'pos_rate_limits-val :lambda-list '(m))
(cl:defmethod pos_rate_limits-val ((m <RTPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:pos_rate_limits-val is deprecated.  Use wam_msgs-msg:pos_rate_limits instead.")
  (pos_rate_limits m))

(cl:ensure-generic-function 'ortn_rate_limits-val :lambda-list '(m))
(cl:defmethod ortn_rate_limits-val ((m <RTPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader wam_msgs-msg:ortn_rate_limits-val is deprecated.  Use wam_msgs-msg:ortn_rate_limits instead.")
  (ortn_rate_limits m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTPose>) ostream)
  "Serializes a message object of type '<RTPose>"
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
   (cl:slot-value msg 'orientation))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'pos_rate_limits))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'ortn_rate_limits))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTPose>) istream)
  "Deserializes a message object of type '<RTPose>"
  (cl:setf (cl:slot-value msg 'position) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'position)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'orientation) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'orientation)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'pos_rate_limits) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'pos_rate_limits)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'ortn_rate_limits) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'ortn_rate_limits)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTPose>)))
  "Returns string type for a message object of type '<RTPose>"
  "wam_msgs/RTPose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTPose)))
  "Returns string type for a message object of type 'RTPose"
  "wam_msgs/RTPose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTPose>)))
  "Returns md5sum for a message object of type '<RTPose>"
  "34cb882fafa374fde18bf3b5e23cd4cd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTPose)))
  "Returns md5sum for a message object of type 'RTPose"
  "34cb882fafa374fde18bf3b5e23cd4cd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTPose>)))
  "Returns full string definition for message of type '<RTPose>"
  (cl:format cl:nil "float32[3] position~%float32[4] orientation~%float32[3] pos_rate_limits~%float32[4] ortn_rate_limits~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTPose)))
  "Returns full string definition for message of type 'RTPose"
  (cl:format cl:nil "float32[3] position~%float32[4] orientation~%float32[3] pos_rate_limits~%float32[4] ortn_rate_limits~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTPose>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'position) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'orientation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'pos_rate_limits) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'ortn_rate_limits) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTPose>))
  "Converts a ROS message object to a list"
  (cl:list 'RTPose
    (cl:cons ':position (position msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':pos_rate_limits (pos_rate_limits msg))
    (cl:cons ':ortn_rate_limits (ortn_rate_limits msg))
))
