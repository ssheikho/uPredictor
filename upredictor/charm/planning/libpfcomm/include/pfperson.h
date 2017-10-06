#ifndef PF_PERSON_H
#define PF_PERSON_H

#include "smcmessagehandler.h"
#include "stopwatch.h"

#include <map>
#include <string>

using namespace std;

class ParamListTable;
class SMCConnection;
class WorldModel;

class PFPerson : public SMCMessageHandler {
	public:
		enum {
			STATE_HAND_EMPTY_NO_PART,
			STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET,
			STATE_WORKING_ON_DOOR,
			STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR,
			STATE_REMOVING_PART,
			START_PART_IN_HAND_HAS_REMOVED_PART
		};

		enum {
			TRANS_HANDOVER_COMPLETE,
			TRANS_WORKER_WORKING_ON_DOOR,
			TRANS_WORKER_NOT_WORKING_ON_DOOR,
			TRANS_WORKER_DISPOSED_PART
		};

		PFPerson(SMCConnection &smc, WorldModel &wm);
		~PFPerson();

		void transitionState(int stateTransition);
		void setPartNo(int partNo);

		void process(const CProtocol::tSMCPayload *payload);

	protected:
		class PartInfo {
			public:
				PartInfo(string thepart, string thedestination,
					string theparttype);
				~PartInfo();

				string _thepart, _thedestination, _theparttype, _nullpart,
					_nullparttype;
		};

		void personInstallsPart(int partNo);
		void personRemovesInstalledPart(int partNo);
		void personDiscardsPart(int partNo);

		int _state, _partNo;
		WorldModel &_wm;
		ParamListTable &_plt;

		string _thePerson;
		map<int, PartInfo *> _m;
		
		StopWatch _sw;
		int _lastState;
};

#endif
