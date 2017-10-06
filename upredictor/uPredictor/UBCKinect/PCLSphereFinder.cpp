#include "PCLSphereFinder.h"

PCLSphereFinder::PCLSphereFinder() {}

PCLSphereFinder::~PCLSphereFinder() {}

void PCLSphereFinder::processType(SimplePool<KinectFrame>::PooledPtr t) {
	t->_spheres.clear();

	map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>> &boxes = t->_boxes;
	for (
		map<int
		, vector < SimplePool<BoxAndConstellation>::PooledPtr >>::iterator
		mIter = boxes.begin(); mIter != boxes.end(); mIter++) {
		vector < SimplePool<BoxAndConstellation>::PooledPtr > &v =
			mIter->second;
		for (vector <SimplePool<BoxAndConstellation>::PooledPtr>::iterator
			vIter = v.begin(); vIter != v.end(); vIter++) {
			//pclRANSAC(t, (*vIter)->getCloud());
		}
	}
}

void PCLSphereFinder::pclRANSAC(
	SimplePool<KinectFrame>::PooledPtr t
	, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud
	
	) {
	std::vector<int> inliers;
	pcl::SampleConsensusModelSphere<pcl::PointXYZRGB>::Ptr
		modelS(new pcl::SampleConsensusModelSphere<pcl::PointXYZRGB>(cloud));
	pcl::RandomSampleConsensus<pcl::PointXYZRGB> ransac(modelS);
	//pcl::RandomSampleConsensus<pcl::PointXYZRGBA> ransac(modelS);
	ransac.setDistanceThreshold(.01);
	ransac.computeModel();
	ransac.getInliers(inliers);

	t->_inliers.setSuperset(&t->_reg);
	t->_inliers.addIndices(inliers);

	//Eigen::VectorXf coeff;
	//ransac.getModelCoefficients(coeff);

	//UBCSphere sphere;
	//sphere._x = coeff[0];
	//sphere._y = coeff[1];
	//sphere._z = coeff[2];
	//sphere._r = coeff[3];
	//t->_spheres[mIter->first].push_back(sphere);
}