#ifndef NON_COMPOUND_AP_H
#define NON_COMPOUND_AP_H

#include "actionpredicate.h"

class NonCompoundAP : public ActionPredicate {
	public:
		NonCompoundAP();
		~NonCompoundAP();

		
		virtual bool meetsPrecond(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params) = 0;
};

#endif
