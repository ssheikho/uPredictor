#include "TrackIDManager.h"
#include "RecNameCollection.h"

#include <fstream>

TrackIDManager::TrackIDManager() {}

TrackIDManager::~TrackIDManager() {
	clear();
}

void TrackIDManager::clear() {
	for (
		vector<TrackID *>::iterator iter = _ids.begin();
		iter != _ids.end(); iter++)
		delete *iter;
	for (
		map<UINT64, TrackIDTable *>::iterator iter = _trackIDTables.begin();
		iter != _trackIDTables.end(); iter++)
		delete iter->second;
}

UINT64 TrackIDManager::getTrackID(UINT64 kinectIndex, UINT64 fromID) {
	map<UINT64, TrackIDTable *>::iterator iter = _trackIDTables.find(kinectIndex);
	TrackIDTable *tidt = NULL;
	if (iter == _trackIDTables.end()) {
		tidt = new TrackIDTable(this, kinectIndex);
		_trackIDTables[kinectIndex] = tidt;
	} else {
		tidt = iter->second;
	}
	return tidt->getTrackID(fromID);
}

void TrackIDManager::save(RecNameCollection &rnc) {
	ofstream f;
	f.open(rnc.getIDFilenameS(), ios::out | ios::binary | ios::trunc);

	int nItems = _ids.size();
	f.write((char *)&nItems, sizeof(int));

	for (vector<TrackID *>::iterator iter = _ids.begin();
	iter != _ids.end(); iter++) {
		TrackID *tid = *iter;
		f.write((char *)&tid->_kinectIndex, sizeof(int));
		f.write((char *)&tid->_fromId, sizeof(UINT64));
	}
}

void TrackIDManager::load(RecNameCollection &rnc) {
	clear();

	ifstream f;
	f.open(rnc.getIDFilenameS(), ios::in | ios::binary);

	int nItems;
	f.read((char *)&nItems, sizeof(int));

	for (int itemNo = 0; itemNo < nItems; itemNo++) {
		int kinectIndex;
		UINT64 fromId;
		f.read((char *)&kinectIndex, sizeof(int));
		f.read((char *)&fromId, sizeof(UINT64));
		getTrackID(kinectIndex, fromId);
	}
}

size_t TrackIDManager::nUINT64s() {
	return _ids.size();
}

UINT64 TrackIDManager::getUINT64(size_t index) {
	return _ids[index]->_toId;
}

TrackIDManager::TrackIDTable::TrackIDTable(
	TrackIDManager *tidm
	, int kinectIndex) :
	_tidm(tidm)
	, _kinectIndex(kinectIndex) {}

TrackIDManager::TrackIDTable::~TrackIDTable() {}

UINT64 TrackIDManager::TrackIDTable::getTrackID(UINT64 fromID) {
	UINT64 retVal = 0;
	map<UINT64, TrackID *>::iterator iter = _trackIDs.find(fromID);
	if (iter == _trackIDs.end()) {
		TrackID *tid = new TrackID();
		tid->_kinectIndex = _kinectIndex;
		tid->_fromId = fromID;
		retVal = tid->_toId = _tidm->_ids.size();

		_tidm->_ids.push_back(tid);
	}
	else {
		retVal = iter->second->_toId;
	}
	return retVal;
}
