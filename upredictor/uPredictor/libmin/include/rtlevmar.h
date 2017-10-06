/* 
////////////////////////////////////////////////////////////////////////////////////
// 
//  Prototypes and definitions for the Levenberg - Marquardt minimization algorithm
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
//	Justin W. Hart - Swiped and modified from LevMar
//
////////////////////////////////////////////////////////////////////////////////////
*/

#ifndef RT_LEVMAR_H
#define RT_LEVMAR_H

#include "rtminimizable.h"
#include <levmar.h>
#include <pthread.h>
#include <semaphore.h>

class RTLevMar {
	public:
		RTLevMar(RTMinimizable &min, double thresh = 0.000001);
		~RTLevMar();

		int rt_dlevmar_dif();
		int lmd(
			void (*func)(double *p, double *hx, int m, int n, void *adata),
			double *p, double *x, int m, int n,
			double info[LM_INFO_SZ], void *adata);

		void startLearnThread();
		void startLearning();
		void stopLearning();

	protected:
		static void *threadHelper(void *data);
		static void rtLevMarEvalDif(
			double *p, double *hx, int m, int n, void *adata);

		int allocWork(int m, int n);
		bool keepIterating();

		RTMinimizable &_min;
		int worksz, using_ffdif, freework, k, itmax;
		double _thresh;
		double tau, eps1, eps2, eps2_sq, eps3, delta;
		double *work;
		double *e, *_hx, *jacTe, *jac, *jacTjac, *Dp, *diag_jacTjac, *pDp,
			*wrk, *wrk2;
		double *_p, _info[LM_INFO_SZ];

		pthread_t _thread;
		sem_t _waitDoneLrn, _waitStartLearn;
		bool _keepGoing;
};


#endif
