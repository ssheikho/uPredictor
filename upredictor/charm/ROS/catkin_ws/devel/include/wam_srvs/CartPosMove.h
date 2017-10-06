/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by gensrv_cpp from file /home/justin/charm/charm/trunk/ROS/catkin_ws/src/wam_srvs/srv/CartPosMove.srv
 *
 */


#ifndef WAM_SRVS_MESSAGE_CARTPOSMOVE_H
#define WAM_SRVS_MESSAGE_CARTPOSMOVE_H

#include <ros/service_traits.h>


#include <wam_srvs/CartPosMoveRequest.h>
#include <wam_srvs/CartPosMoveResponse.h>


namespace wam_srvs
{

struct CartPosMove
{

typedef CartPosMoveRequest Request;
typedef CartPosMoveResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct CartPosMove
} // namespace wam_srvs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::wam_srvs::CartPosMove > {
  static const char* value()
  {
    return "993d3a0cca92114d34b338aeb1007ee4";
  }

  static const char* value(const ::wam_srvs::CartPosMove&) { return value(); }
};

template<>
struct DataType< ::wam_srvs::CartPosMove > {
  static const char* value()
  {
    return "wam_srvs/CartPosMove";
  }

  static const char* value(const ::wam_srvs::CartPosMove&) { return value(); }
};


// service_traits::MD5Sum< ::wam_srvs::CartPosMoveRequest> should match 
// service_traits::MD5Sum< ::wam_srvs::CartPosMove > 
template<>
struct MD5Sum< ::wam_srvs::CartPosMoveRequest>
{
  static const char* value()
  {
    return MD5Sum< ::wam_srvs::CartPosMove >::value();
  }
  static const char* value(const ::wam_srvs::CartPosMoveRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::wam_srvs::CartPosMoveRequest> should match 
// service_traits::DataType< ::wam_srvs::CartPosMove > 
template<>
struct DataType< ::wam_srvs::CartPosMoveRequest>
{
  static const char* value()
  {
    return DataType< ::wam_srvs::CartPosMove >::value();
  }
  static const char* value(const ::wam_srvs::CartPosMoveRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::wam_srvs::CartPosMoveResponse> should match 
// service_traits::MD5Sum< ::wam_srvs::CartPosMove > 
template<>
struct MD5Sum< ::wam_srvs::CartPosMoveResponse>
{
  static const char* value()
  {
    return MD5Sum< ::wam_srvs::CartPosMove >::value();
  }
  static const char* value(const ::wam_srvs::CartPosMoveResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::wam_srvs::CartPosMoveResponse> should match 
// service_traits::DataType< ::wam_srvs::CartPosMove > 
template<>
struct DataType< ::wam_srvs::CartPosMoveResponse>
{
  static const char* value()
  {
    return DataType< ::wam_srvs::CartPosMove >::value();
  }
  static const char* value(const ::wam_srvs::CartPosMoveResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // WAM_SRVS_MESSAGE_CARTPOSMOVE_H