#include "SMC/Client.h"
#include "SMCClient.h"
#include "SMC/SMCProtocol.h"
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace SMC;
using namespace std;


int main(int argc, char* argv[])
{
	SMC::CClient *_smcclient = new CClient(
					"localhost:4003",
					"Planner",
					CProtocol::Planner, 1.0,
					2);

	_smcclient->StartReception();

	CClient::ReceptionStatus receptionStatus;

	while(true)
	{
		receptionStatus = _smcclient->CheckReceptionStatus();

        if (receptionStatus == CClient::rsFail)
        {
           cout << "error occured, rsFail received" << endl;
           break;
        }

		//CClient::rsOkNoNews != We want it
		if (receptionStatus != CClient::rsOkNoNews)
        {  
			//reading 
			//payload incoming message
			const CProtocol::tSMCPayload * payload = _smcclient->GetPayloadPtr();
	   		if (payload == NULL)
				break;

			//backPayload - Message to send to SMC
			char *backPayload = _smcclient->GetBackPayloadPtr();
      		int backPayloadSize = _smcclient->GetBackPayloadSize();

			//ENUM of SMC States
			switch (payload->State)
			{
				case CProtocol::DoWhatNext:
					strncpy(backPayload, "Planner SMC R PlannerReady", backPayloadSize);
				break;

				case CProtocol::DoWhatNext1:
					strncpy(backPayload, "Planner SMC R PlannerACK", backPayloadSize);
				break;

				case CProtocol::DoWhatNext2:
					strncpy(backPayload, "Planner SMC R StartMove1", backPayloadSize);
				break;

				case CProtocol::DoWhatNext3:
					strncpy(backPayload, "Planner SMC R StartMove2", backPayloadSize);
				break;

				case CProtocol::WantStartMove:
					strncpy(backPayload, "Planner SMC R StartMove3 Position=0", backPayloadSize);
				break;

				case CProtocol::WantStartMove1:
					strncpy(backPayload, "Planner SMC R PresentPart1", backPayloadSize);
				break;

				case CProtocol::WantStartMove2:
					strncpy(backPayload, "Planner SMC R PresentPart2", backPayloadSize);
				break;

				case CProtocol::WantStartMove3:
					strncpy(backPayload, "Planner SMC R PresentPart3", backPayloadSize);
				break;

				case CProtocol::WantStartMove4:
					strncpy(backPayload, "Planner SMC R PlannerFinish Position=1", backPayloadSize);
				break;

				default:
					continue;
			}

			//If string is too long, append a zero to the end
			backPayload[backPayloadSize-1]= '\0';
			cout<<payload->State<<"  "<<backPayload<<"\n";

			//Sends the report
			_smcclient->PushReport();

		}
	}
	if(_smcclient != NULL)
		delete _smcclient;
}


