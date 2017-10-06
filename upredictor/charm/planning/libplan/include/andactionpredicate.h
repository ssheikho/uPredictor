#ifndef AND_ACTION_PREDICATE_H
#define AND_ACTION_PREDICATE_H

#include "actionpredicate.h"

#include <map>
#include <vector>

using namespace std;

class AndActionPredicate : public ActionPredicate {
	public:
		AndActionPredicate(vector<ActionPredicate*> &preds,
			bool maintainPointer);
		~AndActionPredicate();

		void printContents(bool cr = true);

		bool preconditionsMet(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params);

		void apply(PlanState &to, ParamList &params, bool invert);

	protected:
		int _npreds;
		ActionPredicate **_preds;
		bool _maintainPointer;
};

#endif
