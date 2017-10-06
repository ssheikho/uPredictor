#ifndef PCL_SPHERE_FINDER_H
#define PCL_SPHERE_FINDER_H

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

class PCLSphereFinder :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	PCLSphereFinder();
	~PCLSphereFinder();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);

protected:
	void pclRANSAC(
		SimplePool<KinectFrame>::PooledPtr t
		, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud);
};

#endif