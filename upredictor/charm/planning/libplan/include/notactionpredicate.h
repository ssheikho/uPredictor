#ifndef NOT_ACTION_PREDICATE_H
#define NOT_ACTION_PREDICATE_H

#include "actionpredicate.h"

class NotActionPredicate : public ActionPredicate {
	public:
		NotActionPredicate(ActionPredicate *pred, bool maintainPointer);
		~NotActionPredicate();

		void printContents(bool cr = true);

		bool preconditionsMet(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params);

		void apply(PlanState &to, ParamList &params, bool invert);
	
	protected:
		ActionPredicate *_pred;
		bool &_maintainPointer;
};

#endif
