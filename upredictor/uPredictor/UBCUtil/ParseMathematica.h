#ifndef PARSE_MATHEMATICA_H
#define PARSE_MATHEMATICA_H

#include <Eigen/Core>
#include <string>

using namespace Eigen;
using namespace std;

string getWholeFile(string fileName);
int countCols(string inLine);
int countRows(string inMat);
void fillMat(int inRowNo, string inLine, MatrixXd &mat);
MatrixXd parseMathematica(string inMat);

#endif
