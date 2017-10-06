#ifndef T3WSMCCLIENT_H
#define T3WSMCCLIENT_H

#include "../BaseSmcClient.h"


class T3wSmcClient : public BaseSmcClient
{
  public:

    T3wSmcClient(const std::string &name);
    bool runLoop();
    bool updateSmc(const SMC::CClient::ReceptionStatus &receptionStatus);
    virtual ~T3wSmcClient();

  protected:

  private:

    std::string _lastSmcMessage;

};

#endif // T3WSMCCLIENT_H
