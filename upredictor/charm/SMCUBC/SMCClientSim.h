/*
* Thierry Moszkowicz (TM)
* April 2012, May 2013, May 2014
*/


#ifndef SMC_CLIENT_EXE_H
#define SMC_CLIENT_EXE_H

#include "PACC/Socket.hpp"
#include "SMC/Client.h"

class SMCClient
{
public:
   ////// Public methods
    SMCClient();
   ~SMCClient();

   int main();

   bool ParseParameters(int argc, char* * argv);
   void PrintParametersHelp(const char * pAppName);

private:
   static const int NAME_SIZE = 128;
   ////// Private types or structs
   struct Params {
      Params();

      char                       mServerAddress[NAME_SIZE]; // Server address (not default value because this parameter is required).
      unsigned int               mMaxIterations;            // Client stop when the maximum iteration is reach. Infinit loop when 0.
      int                        mWait;                     // In ms
      char                       mName[NAME_SIZE];          // Client name.
      //SMC::CProtocol::tSMCModule mSMCModule;à
      int                        mReconnectionDelay;        // Reconnection delay. When >=0, try to reconnect after the timeout when server connection close (or not open yet). In ms
      int                        mReconnectionMaxRetry;     // Max number of reconnection try when a positive reconnection timeout is provided.
      bool                       mIsSMCParamsOk;

      //added DO
      bool                       mSimModule[SMC::CProtocol::NbSMCModules];
      int mVerboseLevel;

   };

   Params mParams;

   ////// Private methods
   bool InTheLoopProcess(SMC::CClient::ReceptionStatus pReceptionStatus, const SMC::CProtocol::tSMCModule &pModule);
   //bool InTheLoopProcessSMC(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload); 
   bool InTheLoopProcessSADB(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload); 
   //bool InTheLoopProcessT1(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload); 
   //bool InTheLoopProcessT2(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessIAD(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessKUKA(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessGRIP(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessT3K(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessT3P(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessT3W(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);
   bool InTheLoopProcessT3O(SMC::CClient::ReceptionStatus pReceptionStatus, char* lReportStr, int lReportSize, const SMC::CProtocol::tSMCPayload* lPayload);

   ////// Private member variables
   SMC::CClient * mSMCClientPtr[SMC::CProtocol::NbSMCModules];
};

#endif //SMC_CLIENT_EXE_H
