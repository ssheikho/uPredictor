#include <osgDB/ReadFile>

#include "Handlers/BaseSadbHandler.h"
#include "SadbBools.h"


using namespace std;


SadbBools::SadbBools(BaseSadbHandler * baseSadbHandler) :
  SadbBase(baseSadbHandler)
{
  //ctor
}


SadbBools::~SadbBools()
{
  //dtor
}


bool SadbBools::pushBools(SADB::Blackboard * blackboard, const std::vector<bool>
  &bools, const std::string &boName, const std::vector<std::string> &catNames,
  const MyTime &timestamp)
{
  // check if valid
  if (!blackboard || boName.empty())
  {
    reset();
    return false;
  }

  std::string funcName = "SadbBools::pushBools";

  // check if need to reset blackboard object
  if (blackboard != _blackboard
    || boName != _boName
    || catNames != _catNames)
  {
    _boName = boName;
    _catNames = catNames;
    _blackboard = blackboard;
    if (!resetPush())
    {
      return false;
    }
  }

  unsigned int r;
  SADB::Timestamp sadbTimestamp;

  // determine timestamp
  if (timestamp.valid())
  {
    sadbTimestamp = timestamp.sadbTime();
  }
  else
  {
    sadbTimestamp.Now();
  }
  _boBools.SetTimestamp(&sadbTimestamp);

  // push points
  if (bools.empty())
  {
    _boBools.SetDimensionsf(0);
  }
  else
  {
    _boBools.SetDimensionsf(1,bools.size());

    for (r=0; r<bools.size(); r++)
    {
      _boBools.SetBoolean(bools.at(r),r);
    }
  }
  if (0 != _boBools.Send())
  {
    OSG_WARN << "Warning " << funcName << "() push failed" << endl;
    reset();
    _baseSadbHandler->disconnect(); // sadb has reconnect bug that blocks so just disconnect for now
    return false;
  }

  return true;
}


void SadbBools::reset()
{
  SadbBase::reset();

  _boName.clear();
  _catNames.clear();
  _boBools = SADB::BlackboardObject();
}


bool SadbBools::resetPull()
{
  return false;
}


bool SadbBools::resetPush()
{
  string funcName = "SadbBools::resetPush";

  // init
  SADB::SADBu64 cuid;
  unsigned int i;

  // set blackboard pointer
  _boBools = SADB::BlackboardObject();
  _boBools.SetDataType(SADB::BOByte);
  _boBools.SetBlackboard(_blackboard);

  // create or get entity's blackboard object Ouids and add to categories
  _boBools.CreateIfNonExistant(_boName.c_str());
  if (0 == _boBools.ID)
  {
    OSG_WARN << "Warning " << funcName
      << "() blackboard object ID invalid, aborting" << endl;
    reset();
    return false;
  }
  _boBools.SetDescription((_boName + " as bool").c_str());

  // create or get categories
  for (i=0; i<_catNames.size(); i++)
  {
    cuid = _blackboard->CreateCategoryIfNonExistant(_catNames.at(i).c_str());
    if (0 == cuid)
    {
      OSG_WARN << "Warning " << funcName
        << "() category ID invalid, aborting" << endl;
      reset();
      return false;
    }
    _blackboard->SetCategoryDescription(cuid,
      (_catNames.at(i) + " as bool").c_str());
    _boBools.AddToCategory(cuid);
  }
  return true;
}
