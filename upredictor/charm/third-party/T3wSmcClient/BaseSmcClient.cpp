#include "BaseSmcClient.h"


using namespace std;


BaseSmcClient::BaseSmcClient(const std::string &name) :
  BaseWeHandler(name),
  // public
  _smcRepeatTimeout(5.0), // double
  _smcVerboseLevel(1), // int
  _smcModule(SMC::CProtocol::UNKNOWN), // SMC::CProtocol::tSMCModule
  // protected
  _smcClient(NULL) // SMC::CClient *
{
  //ctor
}


bool BaseSmcClient::runLoopConnect()
{
#ifdef FAKE_SMC_SERVER
  return true;
#endif

  string funcName = "BaseSmcClient::runLoopConnect";

  // delete old and create new client
  if (_smcClient)
  {
    delete _smcClient;
    _smcClient = NULL;
  }

  _smcClient = new SMC::CClient(_serverAddress,_name.c_str(),
    _smcModule,_smcRepeatTimeout,_smcVerboseLevel);

  return _smcClient->IsOpen();
}


bool BaseSmcClient::runLoopDisconnect()
{
//  string funcName = "BaseSmcClient::runLoopDisconnect";

  if (_smcClient)
  {
    if (_smcClient->IsOpen())
    {
      _smcClient->StopReception();
      _smcClient->RequestQuit();
    }
    delete _smcClient;
    _smcClient = NULL;
  }
  return true;
}


BaseSmcClient::~BaseSmcClient()
{
  //dtor
}
