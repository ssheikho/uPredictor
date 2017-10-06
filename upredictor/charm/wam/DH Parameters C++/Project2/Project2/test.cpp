#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int BUFFSIDE = 100;
const int row = 4;
const int col = 4;

int main() {
	int r, c;
	double array[row][col] = {0};
	char buff[BUFFSIDE];
	ifstream infile("testcsv.csv");
	stringstream ss;
	
	r = 0;
	while (infile.getline(buff, BUFFSIDE) && r < row) {
		ss << buff;
		c = 0;
		while (ss.getline(buff, 10, ',') && c < col) {
			array[r][c] = atof(buff);
			++c;
		}
		ss << " ";
		ss.clear();
		++r;
	}
	for (int _row = 0; _row < 4; ++_row) {
		for (int _col = 0; _col < 4; ++_col) {
			cout << array[_row][_col] << " ";
		}
		cout << "\n";
		cout << endl;
	}
		infile.close();
	
	std::cin.get();

}