#include "stopwatch.h"
#include "UBCUtil.h"

StopWatch::StopWatch() {}
StopWatch::~StopWatch() {}

void StopWatch::resetAndStart() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	_start = _cur = convertSystemTimeToMS(st);
}

double StopWatch::lap() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	_cur = convertSystemTimeToMS(st);

	return _cur = _start;
}

double StopWatch::lapResetTS() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	_cur = convertSystemTimeToMS(st);
	double retVal = _cur - _start;
	_start = _cur;
	return retVal;
}
