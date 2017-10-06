#include "noconcurtable.h"

NoConcurTable::NoConcurTable() {}
NoConcurTable::~NoConcurTable() {}

void NoConcurTable::add(int actionOne, int actionTwo) {
	_m[actionOne].insert(actionTwo);
	_m[actionTwo].insert(actionOne);
}

bool NoConcurTable::isNoConcur(int actionOne, int actionTwo) {
	return _m[actionOne].find(actionTwo) != _m[actionOne].end();
}
