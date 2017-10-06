#include <iostream>
#include "command.h"

using namespace std;

Command::Command(string c, int t) {
  cmdstr = c;
  timestamp = t;
}

int Command::getTimestamp() {
  return timestamp;
}

string Command::getCmdStr() {
  return cmdstr;
}
