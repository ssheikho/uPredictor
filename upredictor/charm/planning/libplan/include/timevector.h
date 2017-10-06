#ifndef TIME_VECTOR_H
#define TIME_VECTOR_H

#include <fstream>
#include <vector>

using namespace std;

class TimeVector {
	
	public:
		TimeVector();
		~TimeVector();

		void addTime(double);
		void printTimes();

		double getMean();
		double getStdDev();
		double getVariance();     
		int getSize();

		void saveTimeData(ofstream &outfile);
		void loadTimeData(ifstream &outfile);
		
	protected:
		void recompute();
		
		vector<double> _tv;
		double _mean;
		double _stdDev;
		double _variance;
		int    _sizeTv;

};

#endif
