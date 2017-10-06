#include "domain.h"
#include "instanceloader.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "pfconfig.h"
#include "planninggraph.h"
#include "problem.h"
#include "timevector.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	PFConfig pf;
	pf.load(argv[1]);
	pf.printContents();

	InstanceLoader il(pf.getDomainFile(), pf.getProblemFile(),
		pf.getConcurrencyFile());

	Domain *d = il.getDomains().getDomain("plugfest");
	Problem *p = d->getProblem("plugfest3");
	p->generatePG();

	ParamListTable &plt = p->getPG().getPLT();
	if(pf.loadTimes())
		plt.loadTimeData(pf.getTimeFile());

	if(pf.saveTimes())
		plt.saveTimeData(pf.getTimeFile());

	/*
	if(true) {
		for(int i = 0; i < 10; i++)
			plt.getPL(10).getTV().addTime(i);

		for(int i = 15; i > 0; i--)
			plt.getPL(15).getTV().addTime(i);

		plt.saveTimeData("test.times");
	} else {
		plt.loadTimeData("test.times");
		plt.getPL(10).getTV().printTimes();
		plt.getPL(15).getTV().printTimes();
	}
	*/

	cout << "10:	" << plt.getPL(10).getTV().getMean() << "	" <<
		plt.getPL(10).getTV().getStdDev() << "	" <<
		plt.getPL(10).getTV().getVariance() << endl;

	cout << "15:	" << plt.getPL(15).getTV().getMean() << "	" <<
		plt.getPL(15).getTV().getStdDev() << "	" <<
		plt.getPL(15).getTV().getVariance() << endl;

	/*
		TimeVector *test = new TimeVector();

		test->addTime(1.1);
		test->addTime(2.2);
		test->addTime(3.3);
		test->addTime(4.4);

		test->printTimes();
	*/
	
	return 0;

}
