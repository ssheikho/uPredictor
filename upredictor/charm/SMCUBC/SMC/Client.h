/*
Client.h
Thierry Moszkowicz April 2012, May 2013, May 2014
*/

#ifndef SMC_CLIENT_LIB_H
#define SMC_CLIENT_LIB_H

#include "SMC.h"
#include "DirectLink/Client.h"
#include "SMCProtocol.h"

namespace SMC {
   using namespace PACC;
   using namespace Socket;


   class LifoStack {
   public:
      ////// Public methods
      LifoStack (int pBuffersSize = 0);

      void SetBuffersSize(int pBuffersSize);

      inline std::string & In() {return mStack[mInIndex];}
      inline const std::string & Out() {return mStack[mOutIndex];}

      int ChangeInIndex();
      int ChangeOutIndex();


      ////// Private member variables
      std::string mStack[3];

      int mInIndex;
      int mOutIndex;
      int mLastIndex;

      Threading::Mutex mIndexMutex;
   };


   class CClient : public CSMC, public DirectLink::CClient, public Threading::Thread
   {

   public:
      //////////////////////////
      ////// Public types //////
      //////////////////////////
      enum ReceptionStatus {rsOkNoNews, rsNewReportRequired, rsNewStateReceived, rsStillReportRequired, rsFail};

      ////////////////////////////
      ////// Public methods //////
      ///////////////////////////
      CClient(const char* pServerAddress, const char* pName, CProtocol::tSMCModule pSMCModule, double pRepeatTimeout = 5.0, int pVerboseLevel = 1);
      ~CClient();

      int StartReception();   //authorize data transfer cycles
      int StopReception();    //pause data transfer cycles 
      int RequestQuit();      //force quit

      inline const char *  GetName() const {return mName;}
      inline char *        GetBackPayloadPtr() const {return mBackPayloadPtr;}
      inline int           GetBackPayloadSize() const {return mBackPayloadSize;}

      const CProtocol::tSMCPayload * GetPayloadPtr();

      inline double GetAgeOfMessage() const {mSafe.lock(); double lTime = getTime(mLastReception); mSafe.unlock(); return lTime;}

      //used by client to wait until next complete message (in progress)
      ReceptionStatus CheckReceptionStatus();

      void PushReport(bool pForceIfNotRequired = false);


      /////////////////////////////////////
      ////// Public member variables //////
      /////////////////////////////////////
      double mPeriod;
      double mLastReception;

      eState mState; //report state


   private:

      /////////////////////////////
      ////// Private methods //////
      /////////////////////////////

      void main(void);

      //////////////////////////////////////
      ////// Private member variables //////
      //////////////////////////////////////

      CProtocol::tSMCModule mSMCModule;

      LifoStack mReceptionLifoStack;

      ReceptionStatus   mReceptionStatus;
      bool              mIsNewStatus;
      bool              mIsReportToPush;           // True when a new report is to send on the back payload
      char *            mBackPayloadPtr;           // Local back payload buffer.
      char *            mLastSentBackPayloadPtr;   // Copy of the last sent back payload
      char *            mLastReceivedStatePtr;     // Copy of the last received state
      double            mLastSentBackPayloadTime;  // Last sent back payload timestamp (for the pooling lock timeout check)
      double            mLastReceivedStateTime;    // last received state time
      double            mRepeatTimeout;            // Pooling lock timeout (in s): a same payload can't be resent before the timeout end
      int               mPayloadSize;              // Maximum size of a payload (initialized by the first message and used to allocate memory for the local payload buffers)
      int               mBackPayloadSize;          // Back payload size (intialized by the first message and used to allocate memory for all the local back payload buffers)
      int               mVerboseLevel;

      Threading::Condition mNewReportToSend;    //Event for a new report to send
      Threading::Mutex mSafe;          //same organisation as server
   };
} // End namespace SMC

#endif //SMC_CLIENT_LIB_H