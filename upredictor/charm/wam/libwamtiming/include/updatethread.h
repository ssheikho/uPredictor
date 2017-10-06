#ifndef UPDATE_THREAD_H
#define UPDATE_THREAD_H

#include "ExternalUpdate.h"
#include <pthread.h>

class UpdateThread : public ExternalUpdate {
	public:
		UpdateThread(ExternalUpdate &eu);
		~UpdateThread();

		static void *updateThread(void *ut);

		void update();
		bool hasFutureUpdates();

		void start();
		void join();

	protected:
		ExternalUpdate &_eu;
		bool _keepGoing;
		pthread_t _t;
};

#endif
