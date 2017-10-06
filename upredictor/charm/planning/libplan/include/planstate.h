#ifndef PLAN_STATE_H
#define PLAN_STATE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class ParamList;
class PlanStatePred;
class PlanStatePredTable;
class Problem;

class PlanState {
	public:
		PlanState(PlanState *state);
		PlanState(Problem *problem, PlanStatePredTable &pspt);
		~PlanState();

		void init(string pred, vector<string> &vals);
		void add(PlanStatePred *p);
		void del(PlanStatePred *p);

		void printContents();

		bool preconditionsMet(ParamList &pl);
		bool postConditionsMet(ParamList &pl);

		Problem &getProblem();
		
		void setIndex(int idx);
		int getIndex();

		bool contains(PlanStatePred &p);
		bool containsAllOf(PlanState &p);
		bool equals(PlanState &p);

	protected:
		Problem *_problem;
		PlanStatePredTable &_pspt;
		int _idx;
		bool _fromCopy;
		map<int, vector<PlanStatePred *> > _state;
};

#endif
