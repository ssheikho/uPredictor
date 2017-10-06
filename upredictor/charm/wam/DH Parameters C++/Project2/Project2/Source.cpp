#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


const int ROWS = 64025;
const int COLS = 53;
const int BUFFSIZE = 80;

//int main() {
//
//	double array[ROWS][COLS];
//	int row, col;
//	char buff[BUFFSIZE];
//	ifstream infile("Trajectories.csv");
//	stringstream ss;
//	
//	for (int row = 0; row < ROWS; ++row) {
//		infile.getline(buff, BUFFSIZE);
//		ss << buff;
//		for (int col = 0; col < COLS; ++col) {
//			ss.getline(buff, 8, ',');
//			array[row][col] = atoi(buff);
//
//		}
//		ss << "";
//		ss.clear();
//	}
//	for (int row = 0; row < ROWS; ++row) {
//		for (int col = 0; col < COLS; ++col) {
//			cout << array[row][col] << " ";
//
//		}
//		cout << endl;
//	}
//	infile.close();
//	return 0;
//
//}