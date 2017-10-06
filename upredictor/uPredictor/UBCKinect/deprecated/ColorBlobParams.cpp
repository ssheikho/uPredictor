#include "ColorBlobParams.h"

ColorBlobParams::ColorBlobParams(
	IndexInterface<wstring> &ii
	, wstring name) :
	_ii(ii)
	, _name(name)
	, _bMinusGThresh(40)
	, _bMinusRThresh(60)
	, _gMinusBThresh(0)
	, _gMinusRThresh(0)
	, _rMinusBThresh(45)
	, _rMinusGThresh(45)

	, _minBlobPts(10)

	, _majorityColorChannel(0)
	, _drawB(rand() % 256)
	, _drawG(rand() % 256)
	, _drawR(rand() % 256)

	//, _gradientThresh(1.0)
{}

ColorBlobParams::~ColorBlobParams() {}

void ColorBlobParams::save(fstream &f) {
	f.write((char *)&_bMinusGThresh._t, sizeof(long));
	f.write((char *)&_bMinusRThresh._t, sizeof(long));

	f.write((char *)&_gMinusBThresh._t, sizeof(long));
	f.write((char *)&_gMinusRThresh._t, sizeof(long));

	f.write((char *)&_rMinusBThresh._t, sizeof(long));
	f.write((char *)&_rMinusGThresh._t, sizeof(long));

	f.write((char *)&_majorityColorChannel._t, sizeof(long));
}

void ColorBlobParams::load(fstream &f) {
	f.read((char *)&_bMinusGThresh._t, sizeof(long));
	f.read((char *)&_bMinusRThresh._t, sizeof(long));

	f.read((char *)&_gMinusBThresh._t, sizeof(long));
	f.read((char *)&_gMinusRThresh._t, sizeof(long));

	f.read((char *)&_rMinusBThresh._t, sizeof(long));
	f.read((char *)&_rMinusGThresh._t, sizeof(long));

	f.read((char *)&_majorityColorChannel._t, sizeof(long));
}

void ColorBlobParams::setName(wstring name) {
	_ii.rename(_name, name);
	_name = name;
}

wstring ColorBlobParams::getName() {
	return _name;
}

int ColorBlobParams::getMaxBoxes() {
	return 5;
}