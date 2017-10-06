#include <time.h>
#include <algorithm>
#include <thread> 
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include "command.h"

using namespace std;

bool compareCmd(Command a, Command b) {
  return a.getTimestamp() < b.getTimestamp();
}

void addCmd(vector<Command> cmdVector, Command cmd) {
  cmdVector.push_back(cmd);
}
  
void deleteCmd(vector<Command> cmdVector, Command cmd) {
  for (size_t i = 0; i < cmdVector.size(); i++) {
    if (cmdVector[i].getCmdStr() == cmd.getCmdStr()) {
      cmdVector.erase(cmdVector.begin()+i);
    }
  }
}

void printCmds(vector<Command> cmdVector) {
  time_t startTime = time(NULL);
  int waittime = cmdVector[0].getTimestamp();

  for (size_t i = 0; i < cmdVector.size(); i++) {
    this_thread::sleep_for (std::chrono::seconds(waittime));
    cout << cmdVector[i].getCmdStr() << endl;
    time_t endTime = time(NULL);
    float timePassed = float(endTime - startTime);	 		// accuracy to seconds only
    waittime = cmdVector[i+1].getTimestamp() - timePassed;
  }
}

int main(int argc, char *argv[]) {
  vector <string> tempstr;
  string tempLine;
  fstream fs;
  fs.open(argv[1], fstream::in);

  vector<Command> commands;

  while (getline(fs, tempLine, '\t')) {
    tempstr.push_back(tempLine);
  }

  for (size_t i = 0; i < tempstr.size(); i+=2) {
    float tempnum; 
    stringstream convert(tempstr[i+1]);
    if (!(convert >> tempnum)) {
      cout << "Failed to convert command time, please check input file" << endl;
      return -1; 
    }

    Command ct(tempstr[i], tempnum);  		// assume input string format is cmd \t time...
    commands.push_back(ct);			// and that every cmd has a time and vice versa
  }

  sort (commands.begin(), commands.end(), compareCmd);
  printCmds(commands);

  return 0;

}
