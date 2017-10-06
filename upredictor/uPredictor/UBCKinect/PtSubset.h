#ifndef PT_SUBSET_H
#define PT_SUBSET_H

#include "FakeWindowsTypes.h"
#include "KinectFrame.h"
#include "Pt3DCollection.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

class PtSubset
	: public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<Pt3DCollection *>
	, public Pt3DCollection {
public:
	PtSubset(int maxPts, int segment, size_t source, size_t which);
	~PtSubset();

	void processType(SimplePool<KinectFrame>::PooledPtr t);

	//Pt3DCollection
	int getNPts();
	CameraSpacePoint *getCameraPt(int index);
	CameraSpacePoint *getCameraPts();
	unsigned char *getRGB();
	
protected:
	int _segment, _ct;
	size_t _source, _which;
	CameraSpacePoint *_cameraSpacePoints;
	unsigned char *_rgb;
};

#endif
