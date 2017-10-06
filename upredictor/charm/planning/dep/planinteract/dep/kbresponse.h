#ifndef KB_RESPONSE_H
#define KB_RESPONSE_H

#include <pthread.h>

class WorldModel;

class KBResponse {
	public:
		static void *kbThread(void *in);

		KBResponse(WorldModel &wm);
		~KBResponse();

		void nextResponse();

		void startThread();
		void waitThread();

	protected:
		WorldModel &_wm;
		pthread_t _thread;
};

#endif
