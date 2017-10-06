#ifndef BASESMCCLIENT_H
#define BASESMCCLIENT_H

//#define FAKE_SMC_SERVER

#include <PACC/Socket/Port.hpp>

#include "BaseWeHandler.h"
#include "SMC/Client.h"


class BaseSmcClient : public BaseWeHandler
{
  public:

    BaseSmcClient(const std::string &name);
    BaseSmcClient * asBaseSmcClientHandler() {return this;}
    virtual ~BaseSmcClient();


    int _smcVerboseLevel;
    double _smcRepeatTimeout;
    std::string _serverAddress;
    SMC::CProtocol::tSMCModule _smcModule;

  protected:

    SMC::CClient * _smcClient;

  private:

    bool runLoopConnect();
    bool runLoopDisconnect();

};

#endif // BASESMCCLIENT_H
