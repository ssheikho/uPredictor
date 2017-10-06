#ifndef ACTION_PREDICATE_H
#define ACTION_PREDICATE_H

#include <map>
#include <vector>

using namespace std;

class ParamList;
class PlanState;
class PlanStatePred;

class ActionPredicate {
	public:
		ActionPredicate();
		~ActionPredicate();

		virtual void printContents(bool cr = true) = 0;

		virtual bool preconditionsMet(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params) = 0;

		virtual void apply(PlanState &to, ParamList &params, bool invert) = 0;
};

#endif
