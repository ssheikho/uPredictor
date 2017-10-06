#ifndef CMDTIMER
#define CMDTIMER

using namespace std;

class Command {
  public:
    Command(string c, int t);
    string getCmdStr();
    int getTimestamp();
    
  private:
    string cmdstr;
    int timestamp;
};

#endif
