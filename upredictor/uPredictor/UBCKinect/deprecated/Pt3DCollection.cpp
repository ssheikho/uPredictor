#include "Pt3DCollection.h"
#include "Point3DRGB.h"

/*
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Pt3DCollection::getCloud() {
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(
		new pcl::PointCloud<pcl::PointXYZRGB>());
	int nPts = getNPts();
	for (int i = 0; i < nPts; i++) {
		cloud->push_back(*getPt(i));
	}
	return cloud;
}
*/