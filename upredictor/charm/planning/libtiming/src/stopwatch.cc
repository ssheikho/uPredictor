#include "stopwatch.h"

#include <iostream>

using namespace std;

StopWatch::StopWatch() {}
StopWatch::~StopWatch() {}

void StopWatch::resetAndStart() {
	clock_gettime(CLOCK_REALTIME, &_start);
}

double StopWatch::lap() {
	clock_gettime(CLOCK_REALTIME, &_cur);
	double elapsed_secs = _cur.tv_sec - _start.tv_sec;
	double elapsed_nsecs = (double)(_cur.tv_nsec - _start.tv_nsec) / 
		1000000000.0;
	_elapsed = elapsed_secs + elapsed_nsecs;

	//cout << "elapsed_secs:	" << elapsed_secs << endl;

	return _elapsed;
}
