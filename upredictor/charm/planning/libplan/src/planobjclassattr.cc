#include "planobjclassattr.h"

PlanObjClassAttr::PlanObjClassAttr() {}
PlanObjClassAttr::~PlanObjClassAttr() {}

void PlanObjClassAttr::addVal(string val) {
	_vals[val] = _vals.size();
}

int PlanObjClassAttr::numVals() {
	return _vals.size();
}

int PlanObjClassAttr::getNumeric(string val) {
	return _vals[val];
}
