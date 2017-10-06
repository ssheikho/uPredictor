#ifndef SMC_CONNECTION_H
#define SMC_CONNECTION_H

#include "outmessageevent.h"

#include "SMC/Client.h"

#include "pthread.h"

#include <vector>

using namespace std;

class PFConfig;
class SMCMessageHandler;

class SMCConnection {
	public:
		static void *smcThread(void *in);
	
		SMCConnection(PFConfig &pfconf);
		~SMCConnection();

		void connect();
		void sendMessage(OutMessageEvent *ome);
		
		void startThread();
		void waitThread();

		void addMessageHandler(SMCMessageHandler *h);

		void sendConnectedResponse();

	protected:
		class ConnectedMessage : public OutMessageEvent {
			public:
				ConnectedMessage();
				~ConnectedMessage();

				void packMessage(char *payload);
		};

		void messageThread();
		void reconnect();

		/*
		void receiveMessage();
		void receiveMessages();

		void sendMessage();
		void sendMessages();
		*/

		PFConfig &_pfconf;
		SMC::CClient *_smcclient;

		pthread_t _thread;
		pthread_mutex_t _mutex;
		vector<OutMessageEvent *> _queue;
		vector<SMCMessageHandler *> _handlers;

		ConnectedMessage _connectedMessage;
};


#endif
