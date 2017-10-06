#ifndef LIB_MIN_H
#define LIB_MIN_H

#include <minimizable.h>
#include <minimizablewithderiv.h>
//#include <minwderandpin.h>

#include "levmar.h"

#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class Minimizable;
class MinimizableWithDeriv;
//class MinWDerAndPin;

void levMarEvalDif(double *p, double *hx, int m, int n, void *adata);
void runLevMarDif(Minimizable *m, int maxIters = -1, bool print = false,
	double thresh = 0.0001);

void runLevMarDer(MinimizableWithDeriv *m, int maxIters = -1);
//void runLevMarDerWPin(MinWDerAndPin *m);

#endif
