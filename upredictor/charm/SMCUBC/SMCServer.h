/*
* Thierry Moszkowicz (TM)
* April 2012, May 2013, May 2014
*/

#ifndef SMC_SERVER_EXE_H
#define SMC_SERVER_EXE_H

#include "SADBClient.h"
#include "SMC/SMCProtocolServer.h"

#include "PACC/Socket.hpp"
#include "string.h"

class SMCServer
{
public:
	SMCServer(void) {}; 

	~SMCServer(void) {};

   static const int NAME_SIZE = 128;

   struct Params {
      Params();

      int                     mServerPort;      // Server port number
      unsigned int            mMaxIterations;   // Maximum iteration (0 for endless loop)
      int                     mNClients;        // Maximum number of clients
      int                     mStackSize;       // Stack size
      int                     mTimeout;         // ms Timeout if no client respond
      char                    mName[NAME_SIZE]; // Server name
      char                    *mScript;         // Script CSV file name
      int                     mVerboseLevel;    // Verbose level (0 for mute mode, 1 for lightly verbose, 2 for mor verbose, ...
	  char                    *mSADBServer;
	  int                     mSADBPort;
      bool                    mParamsOk;
   };

   //// Public member variables
   Params mParams;

   //// Public methods
   int main(int argc, char* argv[]);
   int ParseParameters(int argc, char* * argv);

   bool TrackChanges(SMC::CProtocolServer &pServer, SADBClient* pSADB, double pTime=0.0);

private:
   //// Private methods
   void PrintParametersHelp(const char * pAppName);

   SADBClient *mSADB;

};

#endif //SMC_SERVER_EXE_H
