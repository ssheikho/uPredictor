#include "actorfactory.h"
#include "actortable.h"
#include "concurrentplanresponder.h"
#include "concurrentreplanner.h"
#include "domain.h"
#include "instanceloader.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "pfconfig.h"
#include "pfperson.h"
#include "planninggraph.h"
#include "planresponder.h"
#include "problem.h"
#include "replanner.h"
#include "smcconnection.h"
#include "worldmodel.h"
#include "smcemt.h"
#include "messagemaker.h"

#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	PFConfig pf;
	pf.load(argv[1]);
	pf.printContents();

	InstanceLoader il(pf.getDomainFile(), pf.getProblemFile(),
		pf.getConcurrencyFile());

	Domain *d = il.getDomains().getDomain("plugfest");
	Problem *p = d->getProblem("plugfest3");
	
	ConcurrentReplanner r(*p);
	r.replan(true, NULL);

	ParamListTable &plt = p->getPG().getPLT();
	WorldModel wm(&p->getRootState(), plt);

	SMCConnection smc(pf);
	smc.connect();
	smc.startThread();

	PFPerson person(smc, wm);
	SMCEMT emt(plt, &wm, smc, person, true);
	emt.load(pf.getEMTFile());

	ActorFactory af(wm, emt, smc, person);
	ActorTable at(d->actions(), af);
	at.load(pf.getActorFile());

	smc.addMessageHandler(&person);

	ConcurrentPlanResponder pr(r, wm, at.getATA());
	//KBResponse kb(wm);

	struct timespec to_sleep = { 0, 500 };
	nanosleep(&to_sleep, &to_sleep);
	smc.sendConnectedResponse();
	
	pr.startThread();
	//kb.startThread();
	pr.waitThread();
	smc.waitThread();
	//kb.waitThread(); 
	return 0;
}
