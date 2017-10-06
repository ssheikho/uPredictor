#include "concurrentplangrid.h"

#include <iostream>

using namespace std;

ConcurrentPlanGrid::ConcurrentPlanGrid(int rows, int cols) :
	_rows(rows), _cols(cols) {
	_steps = new ConcurrentPlanStepPtrPtr[rows];
	for(int i = 0; i < rows; i++)
		_steps[i] = new ConcurrentPlanStepPtr[cols];
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j <cols; j++) {
			_steps[i][j] = NULL;
		}
	}
}

ConcurrentPlanGrid::~ConcurrentPlanGrid() {
	for(int i = 0; i < _rows; i++) {
		delete[] _steps[i];
	}
	delete[] _steps;
}

void ConcurrentPlanGrid::set(int row, int col, ConcurrentPlanStep *step) {
	_steps[row][col] = step;
}

ConcurrentPlanStep *ConcurrentPlanGrid::get(int row, int col) {
	return _steps[row][col];
}

void ConcurrentPlanGrid::print() {
	string printable[_rows][_cols];
	for(int i = 0; i < _rows; i++) {
		for(int j = 0; j < _cols; j++) {
			if(_steps[i][j])
				printable[i][j] = _steps[i][j]->getString();
			else
				printable[i][j] = "";
		}
	}

	for(int i = 0; i < _rows; i++) {
		for(int j = 0; j < _cols; j++) {
			cout << "[" << printable[i][j] << "]";
		}
		cout << endl;
	}
}
