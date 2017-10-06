#include "levmardif.h"

LevMarDif::LevMarDif(Minimizable *m, string name,
	int maxIters, bool print, double thresh) :
	_m(m), _maxIters(maxIters), _print(print),
	_thresh(thresh) {
	int workSize = LM_DER_WORKSZ(m->getNParam(), m->getNMeasurement());
	_work = new double[workSize];
	cout << "LevMarDif::LevMarDif:	" << name << "	" << m->getNParam() <<
		"	" << m->getNMeasurement() << "	" << _work << "	" << workSize <<
		endl;

	_opts[0] = 0.00000001;
	_opts[1] = _thresh;
	_opts[2] = _thresh;
	_opts[3] = _thresh*_thresh;
	_opts[4] = -1;
};

LevMarDif::~LevMarDif() {
	delete[] _work;
}

void LevMarDif::update() {
	double *mv = _m->getMeasurementVector();
	int nparam = _m->getNParam();
	int nmeas = _m->getNMeasurement();
	double *p = _m->getInputParameters();

	int nIter =
		dlevmar_dif(
			levMarEvalDif,
			p,
			mv,
			nparam,
			nmeas,
			_maxIters == -1 ? 9999999999 : _maxIters,	//Max iterations
			NULL, _info,
			NULL, //_work,	// this should be set for speed eventually
			NULL, _m);
	_m->setOutputParameters(p);

	if(_print) {
		for(int i = 0; i < LM_INFO_SZ; i++)
			cout << "info[" << i << "] " << _info[i] << endl;
		cout << "runLevMarDif:	" << nIter << endl;
	}
}
