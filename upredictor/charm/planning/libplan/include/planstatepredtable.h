#ifndef PLAN_STATE_PRED_TABLE_H
#define PLAN_STATE_PRED_TABLE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class ObjectTable;
class PlanStatePred;
class Predicate;
class Problem;

class PlanStatePredTable {
	public:
		PlanStatePredTable();
		~PlanStatePredTable();

		void preCacheAllPermutes(Problem *problem);

		PlanStatePred *getPredicate(
			int pred, vector<string> &vals, Problem *problem);
		PlanStatePred *getPredicate(
			int pred, int nobj, int *objs, Problem *problem);

	protected:
		void insertAllPermutes(
			Problem *problem, Predicate &pred, ObjectTable &ot);
		void insertAllPermutes(
			Problem *problem, Predicate &pred, ObjectTable &ot,
			int *objs, int pos);
		void insert(PlanStatePred *p);

		vector<PlanStatePred *> _v;
		map<int, vector<PlanStatePred *> > _preds;
		int _predCtr;
};

#endif
