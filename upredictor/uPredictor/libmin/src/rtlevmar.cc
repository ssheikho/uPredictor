/////////////////////////////////////////////////////////////////////////////////
// 
//  Levenberg - Marquardt non-linear minimization algorithm
//  Copyright (C) 2004  Manolis Lourakis (lourakis at ics forth gr)
//  Institute of Computer Science, Foundation for Research & Technology - Hellas
//  Heraklion, Crete, Greece.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//	Hacked for real-time usage by Justin W. Hart
//
/////////////////////////////////////////////////////////////////////////////////


#include "rtlevmar.h"
#include "libmin.h"
#include <misc.h>
#include <float.h>
#include <iostream>

#define EPSILON       1E-12
#define LM_FINITE finite // ICC, GCC
#define LM_PREFIX d
#define ONE_THIRD     0.3333333334 /* 1.0/3.0 */
#define LM_ADD_PREFIX(s) LM_CAT_(LM_PREFIX, s)
#define AX_EQ_B_BK LM_ADD_PREFIX(Ax_eq_b_BK)
#define LEVMAR_DIF LM_ADD_PREFIX(levmar_dif)
#define LM_CNST(x) (x)
#define LEVMAR_L2NRMXMY LM_ADD_PREFIX(levmar_L2nrmxmy)
#define LEVMAR_FDIF_CENT_JAC_APPROX LM_ADD_PREFIX(levmar_fdif_cent_jac_approx)
#define LEVMAR_FDIF_FORW_JAC_APPROX LM_ADD_PREFIX(levmar_fdif_forw_jac_approx)
#define LEVMAR_TRANS_MAT_MAT_MULT LM_ADD_PREFIX(levmar_trans_mat_mat_mult)
#define LEVMAR_COVAR LM_ADD_PREFIX(levmar_covar)

void RTLevMar::rtLevMarEvalDif(
	double *p, double *hx, int m, int n, void *adata) {
	for(int i = 0; i < n; i++) {
		//cout << "rtLevMarEvalDif:	" << i << "	" << n << endl;
		double a = ((RTMinimizable *)adata)->computeMeasurement(i, p);
		//cout << "rtLevMarEvalDif:	" << i << "	" << n << "	" << a << endl;
		hx[i] = a;
	}
}

//m = _nparam
//n = nmeas
RTLevMar::RTLevMar(RTMinimizable &min, double thresh) : _min(min),
	_thresh(thresh), itmax(500),
	worksz(LM_DIF_WORKSZ(_min.getMaxNParam(), _min.getMaxNMeasurement())),
	work(new double[worksz]),
	_p(new double[_min.getMaxNParam()]),
	_keepGoing(false) {

	int nm = _min.getMaxNMeasurement() * _min.getMaxNParam();
	e = work;
	_hx = e + _min.getMaxNMeasurement();
	jacTe=_hx + _min.getMaxNMeasurement();
	jac=jacTe + _min.getMaxNParam();
	jacTjac=jac + nm;
	Dp=jacTjac + _min.getMaxNParam()*_min.getMaxNParam();
	diag_jacTjac=Dp + _min.getMaxNParam();
	pDp=diag_jacTjac + _min.getMaxNParam();
	wrk=pDp + _min.getMaxNParam();
	wrk2=wrk + _min.getMaxNMeasurement();


	tau=LM_CNST(LM_INIT_MU);
	eps1=LM_CNST(LM_STOP_THRESH);
	eps2=LM_CNST(LM_STOP_THRESH);
	eps2_sq=LM_CNST(LM_STOP_THRESH)*LM_CNST(LM_STOP_THRESH);
	eps3=LM_CNST(LM_STOP_THRESH);
	delta=LM_CNST(LM_DIFF_DELTA);

	using_ffdif=1;
	/*
	tau=0.00000001;
	eps1=_thresh;
	eps2=_thresh;
	eps2_sq=_thresh*_thresh;
	eps3=_thresh*_thresh;
	delta= -1;
	*/
	if(delta<0.0){
		delta=-delta; /* make positive */
		using_ffdif=0; /* use central differencing */
	}

	sem_init(&_waitDoneLrn, 0, 0);
	sem_init(&_waitStartLearn, 0, 0);
	//allocWork(_min.getNParam(), _min.getMaxNMeasurement());	CLEARLY RIGHT
	//allocWork(_min.getNParam(), 1000);		//CLEARLY WRONG
}

RTLevMar::~RTLevMar() {
	delete[] work;
}

int RTLevMar::rt_dlevmar_dif() {
	double *mv = _min.getMeasurementVector();
	int nmeas = _min.getNMeasurement();

	_min.getInputParameters(_p);

	int nIter =
		lmd(rtLevMarEvalDif, _p, mv, _min.getNParam(), nmeas, _info, &_min);
	_min.setOutputParameters(_p);
	//delete[] p;
	//for(int i = 0; i < LM_INFO_SZ; i++)
	//	cout << "info[" << i << "] " << _info[i] << endl;
	cout << "runLevMarDif:	" << nIter << endl;
}

int RTLevMar::allocWork(int m, int n) {
	cout << "allocWork(int m, int n):	" << m << "	" << n << endl;
	freework = 0;

	/*
	worksz=LM_DIF_WORKSZ(m, n); //4*n+4*m + n*m + m*m;
	work=(double *)malloc(worksz*sizeof(double));
	if(!work){
		cerr << "(): memory allocation request failed" << endl;
		return LM_ERROR;
	}
	*/
	freework=1;

	return 0;
}

bool RTLevMar::keepIterating() {
	//cout << "RTLevMar::keepIterating():	" << k << endl; 
	return _keepGoing;//k<itmax;
}

int RTLevMar::lmd(
	void (*func)(double *p, double *hx, int m, int n, void *adata),
	double *p, double *x, int m, int n,
	double info[LM_INFO_SZ], void *adata) {
	k = 0;
	if(n<m){
		//cerr <<
		//	"(): cannot solve a problem with fewer measurements than unknowns"
		//	<< endl;
	} else {
		//allocWork(m, n);
		/* set up work arrays */
		int nm=n*m;
		/*
		e=work;
		hx=e + n;
		jacTe=hx + n;
		jac=jacTe + m;
		jacTjac=jac + nm;
		Dp=jacTjac + m*m;
		diag_jacTjac=Dp + m;
		pDp=diag_jacTjac + m;
		wrk=pDp + m;
		wrk2=wrk + n;
		*/

		register int i, j, l;
		int issolved;

		register double mu, tmp;
		double p_eL2, jacTe_inf, pDp_eL2;
		double p_L2, Dp_L2=DBL_MAX, dF, dL;
		double init_p_eL2;
		int nu, nu2, stop=0, nfev, njap=0, nlss=0, K=(m>=10)? m: 10, updjac,
			updp=1, newjac;

		mu=jacTe_inf=p_L2=0.0; /* -Wall */
		updjac=newjac=0; /* -Wall */

		/* compute e=x - f(p) and its L2 norm */
		(*func)(p, _hx, m, n, adata); nfev=1;
		/* ### e=x-hx, p_eL2=||e|| */
		p_eL2=LEVMAR_L2NRMXMY(e, x, _hx, n);
		init_p_eL2=p_eL2;
		if(!LM_FINITE(p_eL2)) stop=7;

		nu=20; /* force computation of J */

		for(k=0; keepIterating() && !stop; ++k) {
			//
			/* Note that p and e have been updated at a previous iteration */

			// error is small 
			if(p_eL2<=eps3){
				stop=6;
				break;
			}

			if((updp && nu>16) || updjac==K){
				if(using_ffdif){ /* use forward differences */
					LEVMAR_FDIF_FORW_JAC_APPROX(
						func, p, _hx, wrk, delta, jac, m, n, adata);
					++njap; nfev+=m;
				} else { /* use central differences */
					LEVMAR_FDIF_CENT_JAC_APPROX(
						func, p, wrk, wrk2, delta, jac, m, n, adata);
					++njap; nfev+=2*m;
				}
				nu=2; updjac=0; updp=0; newjac=1;
			}

			if(newjac){ /* Jacobian has changed, recompute J^T J, J^t e, etc */
				newjac=0;

				/* J^T J, J^T e */
				if(nm<=__BLOCKSZ__SQ) { // this is a small problem
					register int l;
					register double alpha, *jaclm, *jacTjacim;

					/* looping downwards saves a few computations */
					for(i=m*m; i-->0; ) jacTjac[i]=0.0;
					for(i=m; i-->0; ) jacTe[i]=0.0;

					for(l=n; l-->0; ){
						jaclm=jac+l*m;
						for(i=m; i-->0; ){
							jacTjacim=jacTjac+i*m;
							alpha=jaclm[i]; //jac[l*m+i];
							for(j=i+1; j-->0; ) jacTjacim[j]+=jaclm[j]*alpha;
							jacTe[i]+=alpha*e[l];
						}
					}

					for(i=m; i-->0; ) /* copy to upper part */
					for(j=i+1; j<m; ++j) jacTjac[i*m+j]=jacTjac[j*m+i];
				} else { // this is a large problem
				LEVMAR_TRANS_MAT_MAT_MULT(jac, jacTjac, n, m);

				for(i=0; i<m; ++i) jacTe[i]=0.0;

				for(i=0; i<n; ++i){
					register double *jacrow;

					for(l=0, jacrow=jac+i*m, tmp=e[i]; l<m; ++l)
						jacTe[l]+=jacrow[l]*tmp;
					}
				}

				for(i=0, p_L2=jacTe_inf=0.0; i<m; ++i){
					if(jacTe_inf < (tmp=FABS(jacTe[i]))) jacTe_inf=tmp;
					diag_jacTjac[i]=jacTjac[i*m+i];
					p_L2+=p[i]*p[i];
				}
				//p_L2=sqrt(p_L2);
			}

			// check for convergence
			if((jacTe_inf <= eps1)){
				Dp_L2=0.0; // no increment for p in this case
				stop=1;
				break;
			}

			/* compute initial damping factor */
			if(k==0) {
				for(i=0, tmp=DBL_MIN; i<m; ++i)
					if(diag_jacTjac[i]>tmp) tmp=diag_jacTjac[i];
				mu=tau*tmp;
			}

			for(i=0; i<m; ++i) jacTjac[i*m+i]+=mu;

			/* solve augmented equations */
			#ifdef HAVE_LAPACK
			issolved=AX_EQ_B_BK(jacTjac, jacTe, Dp, m); ++nlss;
			#else
			issolved=AX_EQ_B_LU(jacTjac, jacTe, Dp, m); ++nlss;
			#endif /* HAVE_LAPACK */

			if(issolved) {
					for(i=0, Dp_L2=0.0; i<m; ++i){
						pDp[i]=p[i] + (tmp=Dp[i]);
						Dp_L2+=tmp*tmp;
				}

				if(Dp_L2<=eps2_sq*p_L2){
					stop=2;
					break;
				}

				if(Dp_L2>=(p_L2+eps2)/(LM_CNST(EPSILON)*LM_CNST(EPSILON))){
					stop=4;
					break;
				}

				(*func)(pDp, wrk, m, n, adata); ++nfev;
				pDp_eL2=LEVMAR_L2NRMXMY(wrk2, x, wrk, n);
				if(!LM_FINITE(pDp_eL2)){
					stop=7;
					break;
				}

				dF=p_eL2-pDp_eL2;
				if(updp || dF>0) { /* update jac */
					for(i=0; i<n; ++i) {
						for(l=0, tmp=0.0; l<m; ++l) tmp+=jac[i*m+l]*Dp[l];
						tmp=(wrk[i] - _hx[i] - tmp)/Dp_L2;
						for(j=0; j<m; ++j) jac[i*m+j]+=tmp*Dp[j];
					}
					++updjac;
					newjac=1;
				}

				for(i=0, dL=0.0; i<m; ++i) dL+=Dp[i]*(mu*Dp[i]+jacTe[i]);

				if(dL>0.0 && dF>0.0) {
					tmp=(LM_CNST(2.0)*dF/dL-LM_CNST(1.0));
					tmp=LM_CNST(1.0)-tmp*tmp*tmp;
					mu=mu*((tmp>=LM_CNST(ONE_THIRD)) ?
						tmp : LM_CNST(ONE_THIRD) );
					nu=2;

					for(i=0 ; i<m; ++i) p[i]=pDp[i];

					for(i=0; i<n; ++i){ /* update e, _hx and ||e||_2 */
						e[i]=wrk2[i]; //x[i]-wrk[i];
						_hx[i]=wrk[i];
					}
					p_eL2=pDp_eL2;
					updp=1;
					continue;
				}
			}

			mu*=nu;
			nu2=nu<<1; // 2*nu;

			if(nu2<=nu) {
				stop=5;
				break;
			}

			nu=nu2;

			for(i=0; i<m; ++i) jacTjac[i*m+i]=diag_jacTjac[i];
		}

		for(i=0; i<m; ++i) jacTjac[i*m+i]=diag_jacTjac[i];

		if(info){
			info[0]=init_p_eL2;
			info[1]=p_eL2;
			info[2]=jacTe_inf;
			info[3]=Dp_L2;
			for(i=0, tmp=DBL_MIN; i<m; ++i)
			if(tmp<jacTjac[i*m+i]) tmp=jacTjac[i*m+i];
			info[4]=mu/tmp;
			info[5]=(double)k;
			info[6]=(double)stop;
			info[7]=(double)nfev;
			info[8]=(double)njap;
			info[9]=(double)nlss;
		}

		//free(work);
		//work = NULL;
	}
	_keepGoing = false;
	
	_min.setOutputParameters(&p[0]);
	sem_post(&_waitDoneLrn);
	return k;
}

void *RTLevMar::threadHelper(void *data) {
	RTLevMar *levMar = (RTLevMar *)data;
	for(;;) {
		sem_wait(&levMar->_waitStartLearn);
		levMar->rt_dlevmar_dif();
	}
}

void RTLevMar::startLearnThread() {
	pthread_create(&_thread, NULL, threadHelper, this);
}

void RTLevMar::startLearning() {
	_keepGoing = true;
	sem_post(&_waitStartLearn);
}

void RTLevMar::stopLearning() {
	if(_keepGoing) {
		_keepGoing = false;
		sem_wait(&_waitDoneLrn);
	}
}
