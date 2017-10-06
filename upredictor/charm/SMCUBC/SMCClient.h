/*
* Thierry Moszkowicz (TM)
* April 2012, May 2013, May 2014
*/


#ifndef SMC_CLIENT_EXE_H
#define SMC_CLIENT_EXE_H

#include "PACC/Socket.hpp"
#include "SMC/Client.h"
#include <string.h>

class SMCClient
{
public:
   ////// Public methods
   SMCClient() : mSMCClientPtr(NULL) {memset(mParams.mName, 0, NAME_SIZE);}
   ~SMCClient();

   int main();

   bool ParseParameters(int argc, char* * argv);
   void PrintParametersHelp(const char * pAppName);

private:
   static const int NAME_SIZE = 128;

   ////// Private types or structures
   struct Params {
      inline Params()
         : mMaxIterations(0)        // 0 for endless loop by default
         , mWait(10)                // Wait 10ms in the loop (between two messages) by default
         , mRepeatTimeout(2.0)      // Can't repeat two identical message before 2s by default
         , mReconnectionDelay(-1)   // No reconnection by default
         , mReconnectionMaxRetry(0) // Endless trying loop by default (if the timeout is positive)
         , mVerboseLevel(1)
         , mIsSMCParamsOk(false)
      {}

      char                       mServerAddress[NAME_SIZE];         // Server address (not default value because this parameter is required).
      unsigned int               mMaxIterations;         // Client stop when the maximum iteration is reach. Infinite loop when 0.
      int                        mWait;                  // In ms
      char                       mName[NAME_SIZE];             // Client name.
      SMC::CProtocol::tSMCModule mSMCModule;
      double                     mRepeatTimeout;         // Repeat timeout in s (a message can't be repeat before the end of timeout). In s
      int                        mReconnectionDelay;     // Reconnection delay. When >=0, try to reconnect after the timeout when server connection close (or not open yet). In ms
      int                        mReconnectionMaxRetry;  // Max number of reconnection try when a positive reconnection timeout is provided.
      int                        mVerboseLevel;          // Verbose level. 0 for mute, 1 for lightly verbose, 2 for more verbose, 3 for ...
      bool                       mIsSMCParamsOk;         // Flag set to true when all mandatory program parameter are present and valid.
   };

   Params mParams;


   ////// Private methods
   bool InTheLoopProcess(SMC::CClient::ReceptionStatus pReceptionStatus);


   ////// Private member variables
   SMC::CClient * mSMCClientPtr;
};

#endif //SMC_CLIENT_EXE_H
