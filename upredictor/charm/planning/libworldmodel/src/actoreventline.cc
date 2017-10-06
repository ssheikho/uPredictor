#include "actoreventline.h"
#include "actorplan.h"
#include "paramlist.h"
#include "planstate.h"
#include "problem.h"

#include <cstdlib>
#include <iostream>

using namespace std;

ActorEventLine::ActorEventLine(string name) : _name(name) {}

ActorEventLine::~ActorEventLine() {}

void ActorEventLine::add(ParamList *pl) {
	abort();
	//_timeSlots[ts] = pl;
}

void ActorEventLine::printContents() {
	for(int i = 0; i < _timeSlots.size(); i++)
		printLineAt(i);
	cout << endl;
}

void ActorEventLine::printLineAt(int index) {
		if(_timeSlots[index]) {
			cout << "[";
			_timeSlots[index]->printContents(false);
			cout << "]";
		} else {
			cout << "[-]";
		}
}

int ActorEventLine::getNTimeSteps() {
	return _timeSlots.size();
}


ParamList *ActorEventLine::getPL(int index) {
	return _timeSlots[index];
}

bool ActorEventLine::actionAtTimeSlot(int index) {
	return _timeSlots[index] != NULL;
}

int ActorEventLine::nextNullStart(int startAt) {
	int retVal = startAt;
	int nSteps = getNTimeSteps();
	for(; ((retVal < nSteps) && (_timeSlots[retVal] != NULL)); retVal++);
	return retVal;
}

int ActorEventLine::nextNullEnd(int startAt) {
	int retVal = startAt;
	int nSteps = getNTimeSteps();
	for(; ((retVal < nSteps) && (_timeSlots[retVal] == NULL)); retVal++);
	return retVal;
}

void ActorEventLine::printBrackets(int start, int swap, int end) {
	cout << "==START:	" << start << "	SWAP:	" << swap << "	END:	"
		<< end << "	==" << endl;

	for(int i = 0; i < _timeSlots.size(); i++) {
		printLineAt(i);
		if(i == start)	cout << "+START+";
		if(i == swap)	cout << "+*****+";
		if(i == end)	cout << "+STOP+";
		cout << endl;
		
	}

	for(int i = 0; i < 10; i++) cout << "=";
	cout << endl;
}

bool ActorEventLine::equals(ActorEventLine *ap) {
	bool retVal = ap->getNTimeSteps() == getNTimeSteps();
	for(int i = 0; ((i < getNTimeSteps()) && (retVal)); i++) {
		retVal = _timeSlots[i] == ap->_timeSlots[i];
	}
	return retVal;
}
