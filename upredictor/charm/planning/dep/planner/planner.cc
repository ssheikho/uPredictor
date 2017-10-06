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
#include "pfconfig.h"
#include "plan.h"
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
	PFConfig pf;
	pf.load(argv[1]);
	pf.printContents();

	InstanceLoader il(pf.getDomainFile(), pf.getProblemFile(),
		pf.getConcurrencyFile());

	Domain *d = il.getDomains().getDomain("plugfest");
	Problem *p = d->getProblem("plugfest3");
	p->generatePG();
	p->getPG().doPlanning();

	ParamListTable &plt = p->getPG().getPLT();
	WorldModel wm(&p->getRootState(), plt);

	ActorSorter as(30, &plt);
	//as.process
	ASTable astable(as, wm);
	astable.update(p->getPG().getPlans());

	astable.getPlan(0)->printContents();
	astable.getPlan(0)->getPlan()->printContents();
	astable.getPlan(1)->printContents();
	astable.getPlan(1)->getPlan()->printContents();



	/*
	as.loadPlugfest();
	as.processPLT(&plt);
	ActorPlan *ap = as.processPlan(&p->getPG().getPlans().get(0), wm);
	ap->printContents();
	cout << "==========" << endl;
	ap->compressPlan(wm);
	ap->printContents();
	*/
	/*
	for(int i = 0; i < cpt.getNumberConcurrentPlans(); i++) {
		cout << "========:	" << cpt.getConcurrentPlan(i).getPerformanceTime()
			<< "	" << cpt.getConcurrentPlan(i).getNTimeSteps() << endl;
		//cpt.getConcurrentPlan(i).getPlan().printContents();
		//cpt.getConcurrentPlan(i).printGrid();
	}
	*/
	/*
	r.getCPTT().getFirst()->getPlan().printContents();
	r.getCPTT().getFirst()->printGrid();
	*/
	
	return 0;
}
