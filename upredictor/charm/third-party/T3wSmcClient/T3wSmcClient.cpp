#include "../../Misc/Converter.h"
#include "T3wSmcClient.h"


using namespace std;


T3wSmcClient::T3wSmcClient(const std::string &name) :
  BaseSmcClient(name)
{
  //ctor
}


bool T3wSmcClient::runLoop()
{
  string funcName = "T3wSmcClient::runLoop";

//  OSG_NOTICE << funcName << "() begin" << endl;

  bool worked = false;
  SMC::CClient::ReceptionStatus receptionStatus;

  // check reception status
#ifdef FAKE_SMC_SERVER
  receptionStatus = SMC::CClient::rsFail;
#else
  receptionStatus = _smcClient->CheckReceptionStatus();
#endif

  // update smc
  if (_newWeDataAvailable[eFromSadManager][eWeHuman]
    || SMC::CClient::rsNewReportRequired == receptionStatus
    || SMC::CClient::rsStillReportRequired == receptionStatus)
  {
    OpenThreads::ScopedLock<OpenThreads::ReentrantMutex> lock(_mutex);
    worked = updateSmc(receptionStatus);
    _newWeDataAvailable[eFromSadManager][eWeHuman] = false;
  }

  return worked;
}


bool T3wSmcClient::updateSmc(const SMC::CClient::ReceptionStatus &receptionStatus)
{
  string funcName = "T3wSmcClient::updateSmc";

//  OSG_NOTICE << funcName << "() begin" << endl;

  bool worked = false;
  bool inMainSpace;
  bool inSideSpace;
  bool requestHandover;
  bool requestHelp;
  string smcMessage;
  string workerName;
  unsigned int humanI;
  WorkcellElement * workcellElement;

  // Check the reception status: is all Ok (nothing new), is new State or fail received?, has the last pushed message been sent ?
#ifdef FAKE_SMC_SERVER
  switch (SMC::CClient::rsStillReportRequired)
#else
  switch (receptionStatus)
#endif
  {
    case SMC::CClient::rsOkNoNews: // Nothing new, reception and sent boxes empty

    // smc is waiting for me
    case SMC::CClient::rsNewReportRequired: // A new REPORT REQUIRE a push from you (the SMC is WAITING on you): Please send it when your ready, but send it.
    case SMC::CClient::rsNewStateReceived:  // A new state message as been receive (BE CAREFUL: this state coul'd your own state you just push, this is NORMAL!)
    case SMC::CClient::rsStillReportRequired: // You previously received a rsNewReportRequired, but the SMC is STILL WAITING for your REQUIRED PUSH!

      // generate smc message
      smcMessage = string("T3W SMC R T3WReady");
      for (humanI=0; humanI<_workcellElements.at(eWeHuman).size(); humanI++)
      {
        workcellElement = &(_workcellElements.at(eWeHuman).at(humanI));

        if (!workcellElement->_parameters
          || !workcellElement->_parameters->_id.valid()
          || !workcellElement->_parameters->_isPresentInWorkcell)
        {
          continue;
        }

        workerName = workcellElement->_parameters->_id._name;

        inMainSpace = WorkcellElement::state(workcellElement,eWeDataT3wInMainSpaceTimeFiltered);
        inSideSpace = WorkcellElement::state(workcellElement,eWeDataT3wInSideSpaceTimeFiltered);
        requestHandover = WorkcellElement::state(workcellElement,eWeDataT3wRequestHandoverTimeFiltered);
        requestHelp = WorkcellElement::state(workcellElement,eWeDataT3wRequestHelpTimeFiltered);

        smcMessage = smcMessage
          + " " + workerName + "InMainWorkspace=" + Converter::toString(inMainSpace)
          + " " + workerName + "InSideWorkspace=" + Converter::toString(inSideSpace)
          + " " + workerName + "ReadyForPart=" + Converter::toString(requestHandover)
          + " " + workerName + "HandUp=" + Converter::toString(requestHelp);

        break;
      } // for (humanI=0; humanI<_workcellElements.at(eWeHuman).size(); humanI++)

      // push report
#ifndef FAKE_SMC_SERVER
      if (_smcClient->GetBackPayloadPtr()
        && (unsigned int)_smcClient->GetBackPayloadSize() > smcMessage.length())
      {
#endif
        if (_newWeDataAvailable[eFromSadManager][eWeHuman]
          && _lastSmcMessage != smcMessage)
        {
          _guiMessages.push_back(funcName + "() pushing smc message: "
            + smcMessage);
          _newFltkGuiMessageAvailable = true;
          _lastSmcMessage = smcMessage;
        }
//        else
//        {
//          OSG_NOTICE << funcName << "() pushing smc message: " << smcMessage
//            << endl;
//        }
#ifndef FAKE_SMC_SERVER
        strcpy(_smcClient->GetBackPayloadPtr(),smcMessage.c_str());
        _smcClient->PushReport();
        worked = true;
      }
      else
      {
        _guiMessages.push_back(funcName
          + "() message pointer invalid or message too long for payload");
        _newFltkGuiMessageAvailable = true;
      }
#endif
      break;

    case SMC::CClient::rsFail:
      _guiMessages.push_back(
        (funcName + "() error fsFail received, reconnecting"));
      _newFltkGuiMessageAvailable = true;
      reconnectAttempts(numeric_limits<unsigned int>::max());
      break;

    default:
      _guiMessages.push_back( (funcName
        + "() error unknown smc client reception status"));
      _newFltkGuiMessageAvailable = true;
      disconnect();
      break;
  } // End switch ReceptionStatus

  return worked;
}


T3wSmcClient::~T3wSmcClient()
{
  //dtor
}
