#include "libmin.h"

void levMarEvalDif(double *p, double *hx, int m, int n, void *adata) {
	for(int i = 0; i < n; i++) {
		//cout << "levMarEvalDif:	" << i << "	" << n << endl;
		hx[i] = ((Minimizable *)adata)->computeMeasurement(i, p);
	}
}

void levMarEvalDer(double *p, double *j, int m, int n, void *adata) {
	for(int a = 0; a < m; a++) {
		for(int b = 0; b < n; b++) {
			j[b * m + a] = ((MinimizableWithDeriv *)adata)->computeDerivative(a, b, p);
		}
	}
}

/*
	  tau=LM_CNST(LM_INIT_MU);
	  eps1=LM_CNST(LM_STOP_THRESH);
	  eps2=LM_CNST(LM_STOP_THRESH);
	  eps2_sq=LM_CNST(LM_STOP_THRESH)*LM_CNST(LM_STOP_THRESH);
	  eps3=LM_CNST(LM_STOP_THRESH);
*/

void runLevMarDif(Minimizable *m, int maxIters, bool print, double thresh) {
	double opts[5];
	opts[0] = 0.00000001;
	opts[1] = thresh;
	opts[2] = thresh;
	opts[3] = thresh*thresh;
	opts[4] = -1;

	double *mv = m->getMeasurementVector();
	int nparam = m->getNParam();
	int nmeas = m->getNMeasurement();

	//cout << "runLevMarDif:	" << nparam << "	" << nmeas << endl;

	double info[LM_INFO_SZ];
	double *p = m->getInputParameters();
	double work[LM_DER_WORKSZ(m->getNParam(), nmeas) * 2];

	//for(int i = 0; i < m->getNParam(); i++)
	//	cout << "p[" << i << "]:	" << p[i] << endl;

	int nIter =
		dlevmar_dif(
			levMarEvalDif,
			p,
			mv,
			nparam,
			nmeas,
			maxIters == -1 ? 9999999999 : maxIters,	//Max iterations
			NULL, info,
			work, //NULL,	this should be set for speed eventually
			NULL, m);
	m->setOutputParameters(p);
	//delete[] p;
	if(print) {
		for(int i = 0; i < LM_INFO_SZ; i++)
			cout << "info[" << i << "] " << info[i] << endl;
		cout << "runLevMarDif:	" << nIter << endl;
	}
}

void runLevMarDer(MinimizableWithDeriv *m, int maxIters) {
	double info[LM_INFO_SZ];
	double *p = m->getInputParameters();
	int nIter = dlevmar_der(levMarEvalDif, levMarEvalDer, p, NULL, m->getNParam(), m->getNMeasurement(), 1000, NULL, info, NULL, NULL, m);
	m->setOutputParameters(p);
	cout << "runLevMarDer:	" << nIter << endl;
	for(int i = 0; i < LM_INFO_SZ; i++)
		cout << "info[" << i << "] " << info[i] << endl;
	delete [] p;
}

/*
void runLevMarDerWPin(MinWDerAndPin *m) {
	for(int a = 0; a < m->nFixedPins(); a++) {
		m->updatePrePin();
		m->fixedPin(a);
		m->updatePostPin();

		double info[LM_INFO_SZ];
		double *p = m->getInputParameters();
		int nIter = dlevmar_der(levMarEvalDif, levMarEvalDer, p, NULL, m->getNParam(), m->getNMeasurement(), 1000, NULL, info, NULL, NULL, m);
		m->setOutputParameters(p);
		cout << "runLevMarDer:	" << nIter << endl;
		for(int i = 0; i < LM_INFO_SZ; i++)
			cout << "info[" << i << "] " << info[i] << endl;
		delete [] p;
	}
}
*/


