#include "domain.h"
#include "instanceloader.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "pfconfig.h"
#include "planninggraph.h"
#include "problem.h"

#include <cstdlib>
#include <iostream>

using namespace std;

/*
(:action personInstallsPart
			:parameters		(
								?theperson		-	person
								?thepart		-	part
								?thedestination	-	partdestination
								?theparttype	-	parttype
							)
)
*/

int main(int argc, char **argv){
	PFConfig pf;
	pf.load("../problems/plugfest.conf");
	pf.printContents();

	InstanceLoader il(pf.getDomainFile(), pf.getProblemFile(),
		pf.getConcurrencyFile());

	Domain *d = il.getDomains().getDomain("plugfest");
	Problem *p = d->getProblem("plugfest3");
	p->generatePG();

	ParamListTable &plt = p->getPG().getPLT();

	vector<string> params;
	params.push_back("per1");
	params.push_back("p1");
	params.push_back("d1");
	params.push_back("ptype1");

	ParamList *pl = plt.getPL("personInstallsPart", params);
	pl->printContents(true);

	return 0;
}
