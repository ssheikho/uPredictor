//Interface to SADBServer
//Denis Ouellet
//may 2014

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include <SADB-Client/SADB.h>

// \brief help to generate strings for objects, 
// works like a sprintf
inline const std::string format(const char *fmt, ...) 
{ 
std::string retStr("");
#ifdef WINDOWS
   char buffer[256];
   if (NULL != fmt)
   {
      va_list marker;
      va_start (marker, fmt);
      int nWritten = vsnprintf (buffer,256,fmt, marker);
      //perror (buffer);
      va_end (marker);

      if (nWritten > 0)
         retStr = &buffer[0];
   }
#else
   char* buffer;
   if (NULL != fmt)
   {
      va_list marker;
      va_start (marker, fmt);
      int nWritten = vasprintf (&buffer,fmt, marker);
      va_end (marker);
      if (nWritten > 0)
	  {
         retStr = buffer;
		 free(buffer);
	  }
   }

#endif
	return retStr; 
}


class SADBClient {

public:
	//SADBClient();

	~SADBClient();

	SADBClient(const std::string &pAddress="192.168.1.70", const int pPort=8081);

	int ConnectToServer(const std::string &pAddress, const int pPort);

	bool Disconnect();

	void SetCategory(const std::string &pCategoryName, const std::string &pCategoryDescription = "");
	bool SetObjectCategory(const std::string &pName, const std::string &pCategoryName, const std::string &pCategoryDescription = "");

	size_t PublishBytes(const std::string &pName, const char* pMessage, size_t pSize, double pTimestamp=0.0);

	size_t PublishString(const std::string &pName, const std::string pMessage, double pTimestamp=0.0);
	size_t PublishString2(const std::string &pName, const std::string pMessage, double pTimestamp=0.0); //\brief info = content (maybe slower)
	size_t ReadString(const std::string &pName, std::string &pString, double &pTimestamp);

	bool PublishDouble(const std::string &pName, const double &pValue, double pTimestamp=0.0);
	double ReadDouble(const std::string &pName, double &pTime);
	
	bool PublishFloat(const std::string &pName, const float &pValue, double pTimestamp=0.0);
	double ReadFloat(const std::string &pName, float &pTime);

	bool PublishInteger(const std::string &pName, const int &pValue, double pTimestamp=0.0);
	int ReadInteger(const std::string &pName, double &pTime);

	//\brief using simple double format (no need to carry 2 variables) same as DirectLink and SMC
	inline SADB::Timestamp* ConvertTimestamp(double &pTime) { if(pTime==0.0) mTime.Now(); else mTime.Set(pTime); return &mTime; };
	inline double ConvertTimestamp(SADB::Timestamp &pTimestamp) const { double lTime = pTimestamp.Get(); return lTime; };

	//double getTime(); //\brief return elapsed time in (seconds+decimal fractions) since epoc time (1 JAN 1970)
	//double getTime(const double &pRef); //\brief return elapsed time in seconds since last pRef time (useful for timing)

	////////////////////////////////////////////////////////////////////////////////
	//                                                                            //
	// METHOD      : double getTime()                                             //
	//                                                                            //
	// DESCRIPTION : returns seconds and decimal part in milliseconds since ref   //
	//               time / nor arg = 1 jan 1970                                  //
	//                                                                            //
	////////////////////////////////////////////////////////////////////////////////
	inline static double getTime()
	{
		struct timeb lTp;
		ftime(&lTp);
		double lTime = (double)lTp.time + 0.001f*lTp.millitm;
		return lTime;
	}


	////////////////////////////////////////////////////////////////////////////////
	//                                                                            //
	// METHOD      : double getTime(const double & pRef)                          //
	//                                                                            //
	// DESCRIPTION : returns seconds and decimal part in milliseconds since pRef  //
	//               time                                                         //
	//                                                                            //
	////////////////////////////////////////////////////////////////////////////////

	inline static double getTime(const double &pRef)
	{
		double lTime = getTime();
		if(pRef>0)
			lTime -= pRef;
		return lTime;
	}



private:

	SADB::Blackboard* mBoard;
	SADB::Timestamp mTime;

	//SADB::SADBu64 mCategoryClouds;
	//SADB::SADBu64 mCategoryFeatures;
	//SADB::SADBu64 mCategoryScalars;
	//SADB::SADBu64 mCategoryTransforms;
	//SADB::SADBu64 mCategoryMatrix;
	//SADB::SADBu64 mCategoryParametricModels;
	//SADB::SADBu64 mCategoryStrings;
	SADB::SADBu64 mGeneralCategory;

	//\brief storage of objects
	std::vector<SADB::BlackboardObject*> mIndex;

	//\brief search previously created objects (latest first)... to reach frequent or loop data first and init infos last
	//\should be effective with multiple local SADB clients
	inline SADB::BlackboardObject* SearchObject(const std::string pName)
	{
		//find Object with proper Name... thanks to Oleg
		const auto& lResult = std::find_if(mIndex.rbegin(), mIndex.rend(), [&pName](const SADB::BlackboardObject* pObj)->bool{
			return pObj && pObj->Name && !strcmp( (char*)(pObj->Name), pName.c_str());
		});

		//return nullptr or Object's ptr
		return (lResult==mIndex.rend()?nullptr:*lResult);
	}

	//\brief call this instead of Create() to re-use previous objects for the same purpose
	inline SADB::BlackboardObject* SearchObjectBeforeCreate(const std::string pName, const std::string pDescription, SADB::BODataType pDataType, size_t pRows=0, size_t pCols=0)
	{
		SADB::BlackboardObject* lObject = SearchObject(pName);
		if(lObject)
			return lObject;

		//cout << "create" << endl;

		//create if not exist
		lObject = (SADB::BlackboardObject*)new SADB::BlackboardObject;
		lObject->Create(mBoard, pName.c_str(), pDataType);
		lObject->SetName(pName.c_str()); //mandatory? Create doesn't set local Name?
		lObject->SetDescription(pDescription.c_str());
		lObject->AddToCategory(mGeneralCategory);

		SADB::SADBu32 lDims[2];
		lDims[0] = pRows;
		lDims[1] = pCols;

		if(pRows>0 && pCols>0) 	
			lObject->SetDimensions(2, lDims);
		else if(pRows>0) 
			lObject->SetDimensions(1, lDims);
		else if(pCols>0) 
			lObject->SetDimensions(1, &lDims[1]);

		mIndex.push_back(lObject);
		return lObject;
	}

	//\brief use this to recycle the same reader object for same variable  
	inline SADB::BlackboardObject* SearchObjectBeforeGet(const std::string pName, SADB::BODataType pDataType)
	{
		SADB::BlackboardObject* lObject = SearchObject(pName);
		if(lObject)
			return lObject;

		//create if not exist
		lObject = (SADB::BlackboardObject*)new SADB::BlackboardObject;
		lObject->GetByName(pName.c_str()); 
		//lObject->SetName(pName); //check if necessary or not
		lObject->SetDataType(pDataType);
		mIndex.push_back(lObject);
		return lObject;
	}

	
};
