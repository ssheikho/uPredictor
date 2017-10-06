#ifndef STOP_WATCH_H
#define STOP_WATCH_H

class StopWatch {
	public:
		StopWatch();
		~StopWatch();

		void resetAndStart();
		double lap();
		double lapResetTS();

	protected:
		double _start, _cur, _elapsed;
};

#endif
