#ifndef FRAME_RATE_COUNTER_H
#define FRAME_RATE_COUNTER_H

#include "ExternalUpdate.h"
#include "KinectFrame.h"
#include "StopWatch.h"
#include "TypeBroadcaster.h"

#include <memory>
#include <vector>

using namespace std;

class FrameRateListener;

class FrameRateCounter :
	public ExternalUpdate
	, public TypeBroadcaster<double> {
public:
	FrameRateCounter(int updatePer = 15);
	~FrameRateCounter();

	void update();
	bool hasFutureUpdates();

protected:
	int _updatePer, _count;
	StopWatch _frameRateWatch;
};

#endif