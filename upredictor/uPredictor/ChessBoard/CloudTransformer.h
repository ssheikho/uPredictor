#ifndef CLOUD_TRANSFORMER_H
#define CLOUD_TRANSFORMER_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Eigen>

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

using namespace Eigen;

class CloudTransformer :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
{
public:
	CloudTransformer(Matrix4d rt);
	~CloudTransformer();

	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	Matrix4d _rt;
	
};

#endif