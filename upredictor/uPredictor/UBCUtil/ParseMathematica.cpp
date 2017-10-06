#include "ParseMathematica.h"

#include <fstream>

string getWholeFile(string fileName) {
	ifstream infile(fileName);
	string s, out = "";
	while (!infile.eof()) {	
		getline(infile, s);
		out += s;
	}
	infile.close();
	return out;
}

int countCols(string inLine) {
	inLine = inLine.substr(1);
	int commaDelim = inLine.find(',');
	int endBracketDelim = inLine.find('}');
	int ctr = 0;
	while((commaDelim >= 0) && (commaDelim < endBracketDelim)) {
		//cout << inLine.substr(0, commaDelim) << endl;		
		inLine = inLine.substr(commaDelim + 1);
		commaDelim = inLine.find(',');
		endBracketDelim = inLine.find('}');
		ctr++;
	}
	ctr++;
	//cout << inLine.substr(0, endBracketDelim) << endl;
	return ctr;
}

int countRows(string inMat) {
	int endBracketDelim = inMat.find('}');
	int ctr = 0;
	while(endBracketDelim >= 0) {
		ctr++;
		inMat = inMat.substr(endBracketDelim + 1);
		endBracketDelim = inMat.find('}');
	}
	return ctr - 1;
}

void fillMat(int inRowNo, string inLine, MatrixXd &mat) {
	inLine = inLine.substr(1);
	int commaDelim = inLine.find(',');
	int endBracketDelim = inLine.find('}');
	int ctr = 0;
	while((commaDelim >= 0) && (commaDelim < endBracketDelim)) {
		mat(inRowNo, ctr) =
			strtod(inLine.substr(0, commaDelim).c_str(), NULL);
		//cout << "[" << inLine.substr(0, commaDelim) << "]" << endl;
		inLine = inLine.substr(commaDelim + 1);
		commaDelim = inLine.find(',');
		endBracketDelim = inLine.find('}');
		ctr++;
	}
	mat(inRowNo, ctr) =
		strtod(inLine.substr(0, endBracketDelim).c_str(), NULL);
	//cout << "[" << inLine.substr(0, endBracketDelim) << "]" << endl;
	//cout << "=====" << endl;
}

MatrixXd parseMathematica(string inMat) {
	int startDelim = inMat.find('{');
	string containsRows = inMat.substr(startDelim + 1);
	startDelim = containsRows.find('{');
	int endDelim = containsRows.find('}');

	int rows = countRows(inMat);
	int cols = countCols(containsRows.substr(startDelim, endDelim + 1));
	
	MatrixXd outMat(rows, cols);

	int row = 0;
	while(startDelim >= 0) {
		endDelim = containsRows.find('}');

		fillMat(row, containsRows.substr(startDelim, endDelim + 1), outMat);
		//countCols(containsRows.substr(startDelim, endDelim + 1));

		containsRows = containsRows.substr(endDelim + 1);
		startDelim = containsRows.find('{');

		row++;
	}

	return outMat;
}
