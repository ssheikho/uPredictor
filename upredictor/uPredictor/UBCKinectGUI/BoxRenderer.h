#ifndef BOX_RENDERER_H
#define BOX_RENDERER_H

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

class BoxRenderer :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	BoxRenderer();
	~BoxRenderer();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);

protected:
	cv::Scalar _bbColor;
};

#endif