#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <time.h>

class StopWatch {
	public:
		StopWatch();
		~StopWatch();

		void resetAndStart();
		double lap();

	protected:
		timespec _start, _cur;
		double _elapsed;
};

#endif
