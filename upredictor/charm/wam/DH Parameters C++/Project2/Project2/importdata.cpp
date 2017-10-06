#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;



struct data_t : deque <deque <float> >
{
	typedef deque <deque <float> > ::iterator record_iterator;
	typedef deque        <float>   ::iterator field_iterator;
	typedef vector < tuple<int, string> > markers;
	vector < tuple<int, string> > data_t::column(const string& filename);
	bool load(const string& filename);
	bool save(const string& filename);
	bool save(ostream& outs);
	bool data_t::loadmarker(const string& filename, const int& ColNum);
};

//----------------------------------------------------------------------------
bool data_t::load(const string& filename)
{
	string s;
	ifstream f(filename.c_str());
	while (getline(f, s))
	{
		deque <float> record;
		istringstream iss(s);
		while (getline(iss, s, ','))
		{
			float fieldvalue = 0.0f;
			istringstream(s) >> fieldvalue;
			record.push_back(fieldvalue);
		}
		this->push_back(record);
	}
	return f.good();
}

bool data_t::loadmarker(const string& filename, const int& ColNum)
{
	string s;
	ifstream f(filename.c_str());
	while (getline(f, s))
	{
		deque <float> record;
		istringstream iss(s);
		while (getline(iss, s, ','))
		{
			float fieldvalue = 0.0f;
			istringstream(s) >> fieldvalue;
			record.push_back(fieldvalue);
		}
		this->push_back(record);
	}
	return f.good();
}


vector < tuple<int, string> >  data_t::column(const string& filename) {
	vector < tuple<int, string> > markers;
	int i = 0;
	int colNum = 1;
	string s;
	ifstream f(filename.c_str());
	while (getline(f, s) && i < 3)
	{
		if (i < 2) { i++;  continue; }
		deque <string> record;
		istringstream iss(s);
		while (getline(iss, s, ','))
		{
			string fieldvalue = "";
			istringstream(s) >> fieldvalue;
			record.push_back(fieldvalue);
			if (fieldvalue == "") {
				colNum++;
				continue;
			}
			tuple<int, string> recordTuple(colNum, fieldvalue);
			markers.push_back(recordTuple);
			colNum++;
		}
		i++;
	}

	return markers;
}


//----------------------------------------------------------------------------
bool data_t::save(const string& filename)
{
	ofstream f(filename.c_str());
	if (!f) return false;

	return save(f);
}

//----------------------------------------------------------------------------
bool data_t::save(ostream& outs)
{	
	ofstream outputcsv("NewTrajectories.csv");
	for (data_t::record_iterator ri = this->begin(); ri != this->end(); ri++)
	{
		for (data_t::field_iterator fi = ri->begin(); fi != ri->end(); fi++)
			outputcsv << ((fi == ri->begin()) ? "" : ", ") << *fi;
			
		outputcsv << endl;
	}
	return outs.good();
}

//----------------------------------------------------------------------------
int main()
{
	data_t data;
	string filename;
	cout << "File to read> ";
	getline(cin, filename);

	vector <tuple<int, string>> markerNames = data.column(filename);
	cout << "Available Markers: \n";
	for (tuple<int, string> CurrTuple : markerNames) {
		cout << "Marker Name: " << std::get<1>(CurrTuple) << " Column number: " << std::get<0>(CurrTuple) << "\n";
	}


	/*data.load(filename);

	cout << "The data is:\n";
	data.save(cout);*/

	std::cin.get();
	return 0;
}