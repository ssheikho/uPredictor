#ifndef ATOMIC_ACTION_PREDICATE_H
#define ATOMIC_ACTION_PREDICATE_H

#include "actionpredicate.h"

#include <string>
#include <vector>

using namespace std;

class Action;

class AtomicActionPredicate : public ActionPredicate {
	public:
		AtomicActionPredicate(string name, vector<string> &parameters, 
			Action &action);
		~AtomicActionPredicate();

		void printContents(bool cr = true);

		bool preconditionsMet(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params);

		void apply(PlanState &to, ParamList &params, bool invert);

	protected:
		Action &_action;
		int _predicateID, _nparam, *_parameterMap;
};

#endif
