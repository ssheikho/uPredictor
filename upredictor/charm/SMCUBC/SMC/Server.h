/*
 * Server.h
 * Thierry Moszkowicz May 2012
*/

#include "SMC.h"
#include "DirectLink/Server.h"
#include "SMCProtocolServer.h"
#include <list>

#ifndef SMC_SERVER_LIB_H
#define SMC_SERVER_LIB_H

namespace SMC
{
   using namespace PACC;
   using namespace Socket;


   class CServer : public CSMC, public DirectLink::CServer
   {
   public:
      ////// Methodes
      CServer(char *pName, unsigned int pPort, unsigned int pNClients, int pNBuffers, int pPayloadSize, int pBackPayloadSize, int pVerboseLevel = 1);
      ~CServer(void);

      bool  WaitNextClientReport(int pTimeout);
      inline void  LockBackPayloadList() {mBackPayloadListMutex.lock();}
      inline void  UnlockBackPayloadList() {mBackPayloadListMutex.unlock();}

      inline double GetInitTime() const {return mInitTime;}

      ////// Member variables
      typedef std::list<std::string> tBackPayloadList;
      tBackPayloadList mBackPayloadList;

   protected:
      void NewMessageReceived(const tReport *pReportPtr);
      //for event based reception
      Threading::Condition mSrvTrigger; 
      Threading::Mutex mBackPayloadListMutex;

   private:
      int mVerboseLevel;
      double mInitTime;
   };

} // End namespace SMC

#endif //SMC_SERVER_LIB_H

//end of Server.h

