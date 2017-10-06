#include "actorfactory.h"
#include "actortable.h"
#include "domain.h"
#include "instanceloader.h"
//#include "kbresponse.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "pfconfig.h"
#include "pfperson.h"
#include "plan.h"
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

/*
FILE *inTimes = fopen(argv[4], "r");
yyin = inTimes;
yyparse();
fclose(inTimes);
*/

//class Domain;
//class Problem;

bool arrayCheck(int *a, int *b, int size) {
	bool retVal = true;
	for(int i = 0; i < size; i++)
		retVal &= a[i] == b[i];
	return retVal;
}

int main(int argc, char **argv) {
	/*
	int size = 10000;
	int a[size];
	vector<int> b, c;	
	for(int i = 0; i < size; i++) {
		a[i] = i;
		b.push_back(i);
	}
	c = b;
	cout << "a:	" << arrayCheck(a, a, size) << endl;
	cout << "b:	" << (c == b) << endl;

	ParamListTable &plt = p->getPG().getPLT();

	for(int i = 0; i < plt.size(); i++) {	
		ParamList pl = plt.getPL(i);
		MessageMaker *mm = new MessageMaker(pl);
		mm->printContents(1);
	}

	*/

	PFConfig pf;
	pf.load(argv[1]);
	pf.printContents();

	InstanceLoader il(pf.getDomainFile(), pf.getProblemFile(),
		pf.getConcurrencyFile());

	Domain *d = il.getDomains().getDomain("plugfest");
	Problem *p = d->getProblem("plugfest3");
	
	Replanner r(*p);
	r.replan(true, NULL);
	p->getPG().getPlans().get(0).printContents();
	
	ParamListTable &plt = p->getPG().getPLT();
	plt.setSaveFile(pf.getTimeFile());
	plt.loadTimeData(pf.getTimeFile());
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

	PlanResponder pr(r, wm, at.getATA());
	//KBResponse kb(wm);

	struct timespec to_sleep = { 1, 500 };
	int ret = nanosleep(&to_sleep, &to_sleep);
	cout << "to_sleep:	" << ret << "	" <<
		to_sleep.tv_sec << "	" << to_sleep.tv_nsec <<
		endl;
	smc.sendConnectedResponse();

	ret = nanosleep(&to_sleep, &to_sleep);
	cout << "to_sleep:	" << ret << "	" <<
		to_sleep.tv_sec << "	" << to_sleep.tv_nsec <<
		endl;
	
	pr.startThread();
	//kb.startThread();
	pr.waitThread();
	smc.waitThread();
	//kb.waitThread(); 
	return 0;
	
}


	
	//fillProblem->getPG().getPLT().saveTimeFile(argv[4], "plugfest.times");

	//pg.printSummary();
	//pg.getPlans().printPlans(3);
	//pg.getPST().printStates();
	//pg.printBackMatrix();

	//cout << pg.getConcurrentPlan(0).printContents(-1, 0);
