#include "LongValueArrayEU.h"

LongValueArrayEU::LongValueArrayEU(
	ValueArray<long> *va
	, long index
	, bool loop
	) :
	_va(va)
	, _index(index)
	, _curVal(0)
	, _loop(loop)
{
	_curVal = va->getMinVal(_index) - 1;
}

LongValueArrayEU::~LongValueArrayEU() {}

void LongValueArrayEU::update() {
	if (_loop) {
		_curVal++;
		if (_curVal > _va->getMaxVal(_index))
			_curVal = _va->getMinVal(_index);
		_va->set(_index, _curVal);
	}
	else {
		if (_curVal < _va->getMaxVal(_index)) {
			_curVal++;
			_va->set(_index, _curVal);
		}
	}
}

bool LongValueArrayEU::hasFutureUpdates() {
	return _loop ? true : (_curVal < _va->getMaxVal(_index));
}