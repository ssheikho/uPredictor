#include "actorplan.h"
#include "actorsorter.h"
#include "astable.h"
#include "concurrentplan.h"
#include "concurrentplantable.h"
#include "concurrentreplanner.h"
#include "conplantimetable.h"
#include "domain.h"
#include "domainmap.h"
#include "instanceloader.h"
#include "paramlist.h"
#include "plan.h"
#include "plannerconfig.h"
#include "plannerutil.h"
#include "planninggraph.h"
#include "problem.h"
#include "replanner.h"
#include "stopwatch.h"
#include "worldmodel.h"

#include "planscan.tab.h"

#include <cstdio>
#include <ctime>
#include <iostream>

using namespace std;

extern "C" int yylex ();
extern FILE *yyin;
extern Domain *fillDomain;
extern Problem *fillProblem;
extern DomainMap *domainmap;
extern PlanningGraph *fillPlanningGraph;


int main(int argc, char **argv) {
	PlannerConfig pc;
	pc.load(argv[1]);
	pc.printContents();

	InstanceLoader il(pc.getDomainFile(), pc.getProblemFile(),
		pc.getActorFile());

	Domain *d = il.getDomains().getDomain(pc.getDomainName());
	Problem *p = d->getProblem(pc.getProblemName());
	p->generatePG();
	
	PlanningGraph &pg = p->getPG();
	pg.doPlanning();

	ParamListTable &plt = pg.getPLT();
	WorldModel wm(&p->getRootState(), plt);

	ActorSorter &as = il.getAS();
	as.processPLT(&plt);
	as.printContents();

	//as.process
	ASTable astable(as, wm);
	astable.update(pg.getPlans());

	//astable.getPlan(0)->compressPlan(wm);
	for(int i = 0; i < 0; i++) {
		cout << "=====" << endl;
		astable.getPlan(i)->printContents();
	}
	
	return 0;
}
