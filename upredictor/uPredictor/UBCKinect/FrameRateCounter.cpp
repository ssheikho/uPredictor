#include "FrameRateCounter.h"

FrameRateCounter::FrameRateCounter(int updatePer) :
_updatePer(updatePer), _count(0) {
	_frameRateWatch.resetAndStart();
}

FrameRateCounter::~FrameRateCounter() {}

void FrameRateCounter::update() {
	if (++_count == _updatePer) {
		double frameRate = (double)_updatePer / _frameRateWatch.lapResetTS();

		fireUpdate(frameRate);

		_count = 0;
	}
}

bool FrameRateCounter::hasFutureUpdates() {
	return true;
}