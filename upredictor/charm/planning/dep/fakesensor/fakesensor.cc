#include "SADB-Client/SADB.h"
#include "SMC/Client.h"

#include <cstdlib>
#include <iostream>

using namespace SADB;
using namespace SMC;
using namespace std;

int main(int argc, char **argv){
	Blackboard board;
	int connectionGood = board.ConnectToServer("127.0.0.1", 8081);

	cout << "Board.ConnectToServer:	" << connectionGood << endl;

	BlackboardObject bbo1, bbo2, bbo3;
	bbo1 = SADB::BlackboardObject();
	bbo1.SetDataType(SADB::BOByte);	
	bbo1.SetBlackboard(&board);
	bbo1.CreateIfNonExistant("Matthew WorkerWorkingOnDoor");

	bbo2 = SADB::BlackboardObject();
	bbo2.SetDataType(SADB::BOByte);	
	bbo2.SetBlackboard(&board);
	bbo2.CreateIfNonExistant("Matthew WorkerNotWorkingOnDoor");

	bbo3 = SADB::BlackboardObject();
	bbo3.SetDataType(SADB::BOByte);	
	bbo3.SetBlackboard(&board);
	bbo3.CreateIfNonExistant("Matthew WorkDisposedPart");

	SADB::Timestamp sadbTimestamp;
    sadbTimestamp.Now();

	bbo1.SetTimestamp(&sadbTimestamp);
	bbo2.SetTimestamp(&sadbTimestamp);
	bbo3.SetTimestamp(&sadbTimestamp);
	
	SMC::CClient *_smcclient = new CClient(
					"localhost:4003",
					"T3W",
					CProtocol::T3W, 1.0,
					2);

	_smcclient->StartReception();

	CClient::ReceptionStatus receptionStatus;

	while(true) {
	receptionStatus = _smcclient->CheckReceptionStatus();

		//CClient::rsOkNoNews != We want it
		if (receptionStatus != CClient::rsOkNoNews) { 
			const CProtocol::tSMCPayload * payload =
				_smcclient->GetPayloadPtr();
		}
	}


	char *backPayload = _smcclient->GetBackPayloadPtr();
	int backPayloadSize = _smcclient->GetBackPayloadSize();


	string prefix = "T3W SMC R T3WReady ";
	string postfixWorkingOnDoor =
		"Matthew WorkerWorkingOnDoor=1 WorkerNotWorkingOnDoor=0 WorkerDisposedPart=0";
	string postfixNotWorkingOnDoor =
		"Matthew WorkerWorkingOnDoor=0 WorkerNotWorkingOnDoor=1 WorkerDisposedPart=1";
	string postfixPartDisposed =
		"Matthew WorkerWorkingOnDoor=0 WorkerNotWorkingOnDoor=0 WorkerDisposedPart=1";

	switch(atoi(argv[1])) {
		case 0:
			strncpy(backPayload,
				(prefix + postfixWorkingOnDoor).c_str(), backPayloadSize);
			bbo1.Send();
			break;
		case 1:
			strncpy(backPayload,
				(prefix + postfixNotWorkingOnDoor).c_str(), backPayloadSize);
			bbo2.Send();
			break;
		case 2:
			strncpy(backPayload,
				(prefix + postfixPartDisposed).c_str(), backPayloadSize);
			bbo3.Send();
			break;
	}
	_smcclient->PushReport();
}
