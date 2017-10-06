#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include "GetPos.h"

using namespace std;

struct GetPos::Trajectorie { // struct for coordinate x,y,z of the marker
	string x;
	string y;
	string z;
};

struct GetPos::Marker { // struct for coordinate x,y,z of the marker
	deque<string> x, y, z, TS;
	string MarkerName;
};



void GetPos::parsedata(const string& filename) {
	map<int, string> markers;
	int i = 0;
	int colNum = 1;
	string s;
	ifstream f(filename.c_str());
	vector<Marker> MarkerList;
	while (getline(f, s))  // get the rows of the csv file
	{
		if (i < 2 || i == 3 || i == 4) { i++;  continue; } // skip rows without information
		istringstream iss(s);
		while (getline(iss, s, ','))	// get the element in the row
		{
			string fieldvalue = "";
			istringstream(s) >> fieldvalue;		// asign element to fieldvalue

			if (fieldvalue == "" && colNum < 3) {  // skip first two element of each row
				markers[colNum] = fieldvalue;
				colNum++;
				continue;
			}
			else if (i == 2) { // second row have the marker's names
				markers[colNum] = fieldvalue;

				Marker currMarker;						// create empty struct for each marker
				deque<string> X, Y, Z, TS;
				currMarker.MarkerName = fieldvalue;
				currMarker.x = X;
				currMarker.y = Y;
				currMarker.z = Z;
				currMarker.TS = TS;
				MarkerList.push_back(currMarker);

			}
			else {		
				int currColNum = colNum;

				if (markers[currColNum] == "") {	// skip values until next marker
					colNum++;
					continue;
				}
				else {
					string markerName = markers[currColNum];
					string currX, currY, currZ;
					if (fieldvalue == "") {
						currX = fieldvalue;
						currY = fieldvalue;
						currZ = fieldvalue;
					}
					else {
						currX = fieldvalue;
						getline(iss, s, ',');
						istringstream(s) >> fieldvalue;
						currY = fieldvalue;
						getline(iss, s, ',');
						istringstream(s) >> fieldvalue;
						currZ = fieldvalue;
					}

					int currindex = (currColNum-3);
					
					MarkerList[currindex].x.push_back(currX);
					MarkerList[currindex].y.push_back(currY);
					MarkerList[currindex].z.push_back(currZ);
					MarkerList[currindex].TS.push_back(to_string(i-5));

					colNum = currColNum + 2; // getline jumped 2 positions forward. 
				}
			}

			colNum++;
		}
		i++;
		colNum = 1;
	}

	GetPos::MarkerList = MarkerList;
	
}

const GetPos::Trajectorie GetPos::pos(const string& filename, const int& Frame) {

	Trajectorie T;
	string s;
	ifstream f(filename.c_str());		// read the position for the input frame
	for (int j = 1; j < Frame + 1; j++) {
		getline(f, s);
	}
	string fieldvalue = "";
	istringstream iss(s);
	getline(iss, s, ',');

	istringstream(s) >> fieldvalue;		// assign the value of each axis into the structure
	T.x = fieldvalue;

	getline(iss, s, ',');
	istringstream(s) >> fieldvalue;
	T.y = fieldvalue;

	getline(iss, s, ',');
	istringstream(s) >> fieldvalue;
	T.z = fieldvalue;

	return T;
}

map<int, string> GetPos::column(const string& filename) { // map associate marker's names and columns in the csv file
	map<int, string> markers;
	int i = 0;
	int colNum = 1;
	string s;
	ifstream f(filename.c_str());
	while (getline(f, s))  // get the rows of the csv file
	{
		if (i < 2 || i == 3 || i == 4) { i++;  continue; } // skip rows without information
		istringstream iss(s);
		while (getline(iss, s, ','))	// get the element in the row
		{
			string fieldvalue = "";
			istringstream(s) >> fieldvalue;		// asign element to fieldvalue

			if (fieldvalue == "" && colNum < 3) {  // skip first two element of each row
				markers[colNum] = fieldvalue;
				colNum++;
				continue;
			}
			/*int index = fieldvalue.find(":");
			if (index != -1) {
			fieldvalue.replace(index, 1, "");
			}*/
			else if (i == 2) { // second row have the marker's names
				int index = fieldvalue.find(":");	// replace : on markers name.
				if (index != -1) {
					fieldvalue.replace(index, 1, "");
				}
				ofstream outputcsv;
				outputcsv.open(fieldvalue + ".csv");		// create csv files for each marker
				outputcsv.close();
				markers[colNum] = fieldvalue;
			}
			else {		//else if(i > 4)
				int currColNum = colNum;

				if (markers[currColNum] == "") {	// skip values until next marker
					colNum++;
					continue;
				}
				else {
					string markerName = markers[currColNum];
					string currX, currY, currZ;
					if (fieldvalue == "") {
						currX = fieldvalue;
						currY = fieldvalue;
						currZ = fieldvalue;
					}
					else {
						currX = fieldvalue;
						getline(iss, s, ',');
						istringstream(s) >> fieldvalue;
						currY = fieldvalue;
						getline(iss, s, ',');
						istringstream(s) >> fieldvalue;
						currZ = fieldvalue;
					}

					ofstream outputcsv;
					outputcsv.open(markerName + ".dat", std::ios::app);		// open and append values
					outputcsv << currX + "," + currY + "," + currZ + "\n";
					outputcsv.close();

					colNum = currColNum + 2; // getline jumped 2 positions forward. 
				}
			}

			colNum++;
		}
		i++;
		colNum = 1;
	}

	return markers;
}

const vector<double> GetPos::get(const string& MarkerName, const int& Frame) {

	vector<double> T ;
	string s;

	Marker outputMarker;

	for each (Marker currMarker in GetPos::MarkerList)
	{
		if (currMarker.MarkerName == MarkerName) {
			outputMarker = currMarker;
			break;
		}
	}

	T.push_back(atof(outputMarker.x.at(Frame - 1).c_str()));
	T.push_back(atof(outputMarker.y.at(Frame - 1).c_str()));
	T.push_back(atof(outputMarker.z.at(Frame - 1).c_str()));

	
	return T;
}

int main()
{
	GetPos data;
	string filename, F;
	int Frame;

	cout << "File to read> ";
	getline(cin, filename);

	data.parsedata(filename);
	
	vector <double> testoutput = data.get("Jorge:RPinkie", 11000);

	cout << testoutput[0] << "," << testoutput[1] << "," << testoutput[2];
	
	std::cin.get();
	return 0;
}