#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "action.h"
#include "objecttable.h"
#include "timevector.h"

using namespace std;

//class Action;
//class ObjectTable;
class ParamList;
class ParamListTable;
class PlanState;
class PlanStatePred;
class Problem;

class ParamList {
	public:
		ParamList(Action &action, ObjectTable &ot, Problem *problem,
			int nvals, int *vals, ParamListTable *plt);
		~ParamList();

		void printContents(bool cr = true);

		bool preconditionsMet(map<int, vector<PlanStatePred *> > &pred);
		bool postConditionsMet(map<int, vector<PlanStatePred *> > &pred);
		int getParamObj(int index);
		string getConcreteParam(int index);

		Action &getAction();
		ObjectTable &getObjectTable();
		Problem *getProblem();

		void setIndex(int index);
		int getIndex();
		int getNVals();

		PlanState *doAction(PlanState *to, bool checkExists = true);
		void applyToPlanState(PlanState *state);

		double getTimeMean();
		double getTimeStdDev();

		//void setTimeMean(double t);
		//void setTimeStdDev(double t);

		void save(ofstream &o);

		void addTime(double time);
		TimeVector &getTV();

	protected:

		Action &_action;
		ObjectTable &_ot;
		Problem *_problem;
		int _nvals, *_vals, _index;
		ParamListTable *_plt;
		TimeVector _tv;
		//double _meanTime, _stdDevTime;
		string _command;
};

#endif
