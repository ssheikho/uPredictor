#include "SADB-Client/SADB.h"

#include <iostream>

using namespace SADB;

using namespace std;

int main(void){
	Blackboard board;
	int connectionGood = board.ConnectToServer("127.0.0.1", 8081);

	cout << "Board.ConnectToServer:	" << connectionGood << endl;

	BlackboardObject bbo;
	bbo.SetBlackboard(&board);
	bbo.GetByName("SMC.Begin.Begin");

	bbo.GetLatestValue();
	cout << "Time Stamp:	" << 
		bbo.Time.Second  << "	" <<
		bbo.Time.Millisecond   << "	" <<
		bbo.Time.Get()   << endl;

	double a = bbo.GetDouble(0);
	cout << "Value:	" << a << endl;
}
