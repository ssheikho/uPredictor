#ifndef COLOR_BLOB_PARAMS_H
#define COLOR_BLOB_PARAMS_H

#include "IndexInterface.h"
#include "ValueListener.h"

#include <fstream>
#include <map>
#include <string>

using namespace std;

class ColorTracker;

class ColorBlobParams {
public:
	ColorBlobParams(
		IndexInterface<wstring> &ii
		, wstring name);
	~ColorBlobParams();

	void save(fstream &f);
	void load(fstream &f);

	void setName(wstring name);
	wstring getName();

	int getMaxBoxes();

protected:
	IndexInterface<wstring> &_ii;
	wstring _name;

public:
	ValueListener<long>
		_bMinusGThresh
		, _bMinusRThresh
		, _gMinusBThresh
		, _gMinusRThresh
		, _rMinusBThresh
		, _rMinusGThresh

		, _minBlobPts

		, _majorityColorChannel

		, _drawB
		, _drawG
		, _drawR;

	//ValueListener<double>
	//	_gradientThresh;
};

#endif