#include "smcconnection.h"
#include "pfconfig.h"
#include "smcmessagehandler.h"

#include "SMC/Client.h"
#include "SMCClient.h"
#include "SMC/SMCProtocol.h"

#include <string.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

using namespace SMC;
using namespace std;

void *SMCConnection::smcThread(void *in) {
	SMCConnection *smcConnection = (SMCConnection *)in;
	smcConnection->messageThread();
}

SMCConnection::SMCConnection(PFConfig &pfconf) :
	_pfconf(pfconf), _smcclient(NULL) {
	pthread_mutex_init(&_mutex, NULL); 
}

SMCConnection::~SMCConnection() {}

void SMCConnection::connect() {
	if(_pfconf.connectToSMC()) {
		while(!_smcclient) {
			cout << "Connecting to SMC:	" << _pfconf.getSMCServerAddr() <<
				"	" << _pfconf.getSMCClientName() << endl;
			_smcclient = new CClient(
				_pfconf.getSMCServerAddr().c_str(),
				_pfconf.getSMCClientName().c_str(),
				CProtocol::Planner, 1.0,
				_pfconf.getSMCVerbosity());
			if(!_smcclient->IsOpen()) {
				delete _smcclient;
				_smcclient = NULL;
				cout << "Client didn't open" << endl;
			}
		}
		cout << "/Connecting to SMC:	" << _pfconf.getSMCServerAddr() <<
			"	" << _pfconf.getSMCClientName() << endl;
	}
}

void SMCConnection::reconnect() {
	if(_pfconf.connectToSMC()) {
		while((!_smcclient) || (!_smcclient->IsOpen())) {
			if(!_smcclient->IsOpen()) {
				delete _smcclient;
				_smcclient = NULL;
			}

			cout << "Connecting to SMC:	" << _pfconf.getSMCServerAddr() <<
				"	" << _pfconf.getSMCClientName() << endl;
			_smcclient = new CClient(
				_pfconf.getSMCServerAddr().c_str(),
				_pfconf.getSMCClientName().c_str(),
				CProtocol::Planner, 1.0,
				_pfconf.getSMCVerbosity());
		}
	}
}

void SMCConnection::sendMessage(OutMessageEvent *ome)  {
	pthread_mutex_lock(&_mutex);
	_queue.push_back(ome);
	pthread_mutex_unlock(&_mutex);

/*	const CProtocol::tSMCPayload * lPayloadPtr = _smcclient->GetPayloadPtr();
        if (lPayloadPtr == NULL)
           return false; //(NULL when no payload has never been received yet)

        if (lPayloadPtr->Message[0] != '\0')
           cout << "Client App payload = " << lPayloadPtr->Message;
        else
           cout << "Client App empty payload (echo)" << endl;

        char *lBackPayloadPtr   = _smcclient->GetBackPayloadPtr();
        int lBackPayloadSize    = _smcclient->GetBackPayloadSize();

	strncpy(lBackPayloadPtr, "T1  SMC R T1Ready", lBackPayloadSize);
	lBackPayloadPtr[lBackPayloadSize-1]= '\0';
   
        _smcclient->PushReport(); ////// Unlock client and send response to server */
}

/*
void SMCConnection::receiveMessage()  {
	const CProtocol::tSMCPayload *payload = _smcclient->GetPayloadPtr();
	cout<<"Payload State: " <<payload->State <<"\n";
}

void SMCConnection::receiveMessages()  {
	pthread_mutex_lock(&_mutex);
	CClient::ReceptionStatus receptionStatus =
		_smcclient->CheckReceptionStatus();
	
	while(receptionStatus != CClient::rsOkNoNews || 
		  receptionStatus != CClient::rsFail) {  
		receiveMessage();
		receptionStatus = _smcclient->CheckReceptionStatus();
	}
	pthread_mutex_unlock(&_mutex);
}

void SMCConnection::sendMessage() {
	OutMessageEvent *ome = _queue.front();

	char *lBackPayloadPtr   = _smcclient->GetBackPayloadPtr();
	int lBackPayloadSize    = _smcclient->GetBackPayloadSize();

	ome->packMessage(lBackPayloadPtr);

	_queue.erase(_queue.begin());
}

void SMCConnection::sendMessages() {
	pthread_mutex_lock(&_mutex);
	while(_queue.size())
		sendMessage();
	pthread_mutex_unlock(&_mutex);
}
*/

void SMCConnection::startThread() {
	pthread_create(&_thread, NULL, smcThread, this);
}

void SMCConnection::waitThread()  {
	pthread_join(_thread, NULL);
}

void SMCConnection::addMessageHandler(SMCMessageHandler *h) {
	cout << "SMCConnection::addMessageHandler:	" << h << endl;
	if(!h) abort();
	pthread_mutex_lock(&_mutex);
	_handlers.push_back(h);
	pthread_mutex_unlock(&_mutex);
}

void SMCConnection::sendConnectedResponse() {
	sendMessage(&_connectedMessage);
}

/*
void SMCConnection::messageThread() {
	CClient::ReceptionStatus receptionStatus;
	char *bpp = NULL;
	string lastMessage = "";
	while(true) {
		receptionStatus = _smcclient->CheckReceptionStatus();
        if((receptionStatus == CClient::rsFail) || (!_smcclient->IsOpen())) {
			reconnect();
		} else {
			
			if (receptionStatus != CClient::rsOkNoNews) { 
				pthread_mutex_lock(&_mutex);
				vector<SMCMessageHandler *> activeHandlers = _handlers; 
				pthread_mutex_unlock(&_mutex);

				const CProtocol::tSMCPayload *payload = _smcclient->GetPayloadPtr();
				for(int i = 0; i < activeHandlers.size(); i++) {
					//cout <<
					//	"SMCConnection::messageThread():	activeHandlers:	" <<
					//	activeHandlers.size() << endl;
					activeHandlers[i]->process(payload);
				}				
				receptionStatus = _smcclient->CheckReceptionStatus();
			}

			pthread_mutex_lock(&_mutex);
			if(_queue.size()) {
				//cout << "SMCConnection::messageThread():	" <<
				//	_queue.size() << endl;
				OutMessageEvent *ome = _queue.front();
				bpp = _smcclient->GetBackPayloadPtr();
				if(bpp) {
					ome->packMessage(bpp);
					_queue.erase(_queue.begin());
				}
			} else {
				if(bpp)
					lastMessage = bpp;
			}
			pthread_mutex_unlock(&_mutex);
		}
		
		//
		//receiveMessages();
		//sendMessages();
		//msleep(10);
		//
		if(!_smcclient->IsOpen()) {
			reconnect();
		}

		if(bpp)	{
			lastMessage = bpp;
			_smcclient->PushReport();
			cout << bpp << endl;

			struct timespec to_sleep = { 1, 500 };
			int ret = nanosleep(&to_sleep, &to_sleep);
			cout << "to_sleep:	" << ret << "	" <<
				to_sleep.tv_sec << "	" << to_sleep.tv_nsec <<
				endl;
		}
	}
}
*/


void SMCConnection::messageThread() {
	CClient::ReceptionStatus receptionStatus;
	char *bpp = NULL;
	string lastMessage = "";
	int ctr = 0;
	while(true) {
		receptionStatus = _smcclient->CheckReceptionStatus();
        if((receptionStatus == CClient::rsFail) || (!_smcclient->IsOpen())) {
			reconnect();
		} else {
			
			bool receivedOne = false;
			if (receptionStatus != CClient::rsOkNoNews) { 
				pthread_mutex_lock(&_mutex);
				vector<SMCMessageHandler *> activeHandlers = _handlers; 
				pthread_mutex_unlock(&_mutex);

				const CProtocol::tSMCPayload *payload = _smcclient->GetPayloadPtr();
				for(int i = 0; i < activeHandlers.size(); i++) {
					//cout <<
					//	"SMCConnection::messageThread():	activeHandlers:	" <<
					//	activeHandlers.size() << endl;
					activeHandlers[i]->process(payload);
				}				
				receptionStatus = _smcclient->CheckReceptionStatus();
				receivedOne = true;
			}

			if((receivedOne) || ((ctr++)%10)) {
				pthread_mutex_lock(&_mutex);
				if(_queue.size()) {
					//cout << "SMCConnection::messageThread():	" <<
					//	_queue.size() << endl;
					OutMessageEvent *ome = _queue.front();
					bpp = _smcclient->GetBackPayloadPtr();
					if(bpp) {
						ome->packMessage(bpp);
						//cout << bpp << endl;
						_queue.erase(_queue.begin());
					}
				} else {
					if(bpp)
						lastMessage = bpp;
				}
				pthread_mutex_unlock(&_mutex);
			} else {
				//cout << "Not attempting to send" << endl;
			}
		}
		
		//
		//receiveMessages();
		//sendMessages();
		//msleep(10);
		//
		if(!_smcclient->IsOpen()) {
			reconnect();
		}

		if(bpp)	{
			if(strlen(bpp)) {
				lastMessage = bpp;
			} else {
				strcpy(bpp, lastMessage.c_str());
			}
			if(strlen(bpp))
				//cout << bpp << endl;

			struct timespec to_sleep = { 0, 500 };
			//int ret = nanosleep(&to_sleep, &to_sleep);
			//usleep(500);
			//sleep(1);
			//cout << "to_sleep:	" << ret << "	" <<
			//	to_sleep.tv_sec << "	" << to_sleep.tv_nsec <<
			//	endl;
		}
		_smcclient->PushReport();
	}
}

SMCConnection::ConnectedMessage::ConnectedMessage() {}
SMCConnection::ConnectedMessage::~ConnectedMessage() {}

void SMCConnection::ConnectedMessage::packMessage(char *payload) {
	cout << "SMCConnection::ConnectedMessage::packMessage:	" <<
		"Planner SMC R PlannerReady" << endl;
	strcpy(payload, "Planner SMC R PlannerReady");
}
