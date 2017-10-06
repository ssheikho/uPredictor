#include "messagemaker.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

MessageMaker::MessageMaker(ParamList &pl) :
	_pl(pl) {}

MessageMaker::~MessageMaker() {}

string MessageMaker::getMessage() {
	string retVal = "";

	string ActionName = _pl.getAction().getName();

	if(strcmp(ActionName.c_str(), "firstPartFromRackOfFirstType") == 0 ||
	strcmp(ActionName.c_str(), "firstPartFromRackOfSubsequentType") == 0 ||
	strcmp(ActionName.c_str(), "innerPartFromRack") == 0) {
		int ParamObject = 0;	
		string ParamObjectName = "";
		ParamObject = _pl.getParamObj(1);
		ParamObjectName = _pl.getObjectTable().getObjectName(ParamObject);

		if(strcmp(ParamObjectName.c_str(), "p1") == 0) {
			retVal = "Planner SMC R GetPart FetchPart=1";
		} else if(strcmp(ParamObjectName.c_str(), "p2") == 0) {
			retVal = "Planner SMC R GetPart FetchPart=2";
		} else if(strcmp(ParamObjectName.c_str(), "p3") == 0) {
			retVal = "Planner SMC R GetPart FetchPart=3";
		} else if(strcmp(ParamObjectName.c_str(), "p4") == 0) {
			retVal = "Planner SMC R GetPart FetchPart=4";
		}
	} else if(strcmp(ActionName.c_str(), "moveToPerson") == 0) {
		retVal = "Planner SMC R MoveToPerson";
	} else if(strcmp(ActionName.c_str(), "handOverToPerson") == 0) {
		retVal = "Planner SMC R StartHandover";
	} else if(strcmp(ActionName.c_str(), "moveFromPerson") == 0) {
		retVal = "Planner SMC R StartMoveBack";
	}

	return retVal;
}

void MessageMaker::printContents(bool cr) {
	cout << "MessageMaker:	" << getMessage() << endl;
}
