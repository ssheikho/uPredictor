#include "printactor.h"
#include "actiontoactor.h"
#include "paramlist.h"

#include <iostream>

using namespace std;

PrintActor::PrintActor(string name, int id, ActionToActor &ata,
	WorldModel &wm) :
	Actor(name, id, ata, wm) {}
PrintActor::~PrintActor() {}

void PrintActor::execute(ParamList *pl) {
	cout << "ACTOR:	TYPE:	PrintActor	" << _name << "	EXECUTING:	";
	pl->printContents(true);
}

void PrintActor::configure() {
	cout << "ACTOR:	TYPE:	PrintActor	" << _name << "	CONFIGURING";
}

/*Check SMC state.  If it was the last state, then continue.  If it is the initial state, reset the planner.

It may be faster for the robot to plan servotoperson, then to deal with the variance timings in handovertoperson


	(:joint-actions
		(:joint-action handOverToPerson
			(:actors robot operator)
			(:notifier robot)
		)
	)

*/
