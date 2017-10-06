#ifndef POINT_3D_RGB_H
#define POINT_3D_RGB_H

//#define PCL_NO_PRECOMPILE
//#include <pcl/point_types.h>
//#include <pcl/point_cloud.h>
//#include <pcl/io/pcd_io.h>

struct Point3DRGB {
	float _x2D, _y2D;
	bool _colorIsGood;
	int _indexInDepthImage;
	char r, gb, b;
};

#endif