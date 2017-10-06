#ifndef CONCURRENT_PLAN_GRID_H
#define CONCURRENT_PLAN_GRID_H

#include "concurrentplanstep.h"

class ConcurrentPlanGrid {
	public:
		ConcurrentPlanGrid(int rows, int cols);
		~ConcurrentPlanGrid();

		void print();

		void set(int row, int col, ConcurrentPlanStep *step);
		ConcurrentPlanStep *get(int row, int col);

		ConcurrentPlanStepPtrPtrPtr _steps;
		int _rows, _cols;
};

#endif
