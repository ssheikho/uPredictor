#ifndef FAKE_WINDOWS_TYPES_H
#define FAKE_WINDOWS_TYPES_H

#include <pointxy.h>
#include <pointxyz.h>

#include <x86_64-linux-gnu/sys/types.h>

typedef u_int64_t UINT64;
typedef u_int16_t UINT16;
typedef struct PointXYZ CameraSpacePoint;
typedef struct PointXY ColorSpacePoint;

#endif
