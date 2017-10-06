#ifndef TRACK_ID_MANAGER_H
#define TRACK_ID_MANAGER_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#endif

#include "UINT64List.h"

#include <map>
#include <vector>

using namespace std;

class RecNameCollection;

class TrackIDManager : public UINT64List {
public:
	TrackIDManager();
	~TrackIDManager();

	UINT64 getTrackID(UINT64 kinectIndex, UINT64 fromID);

	void save(RecNameCollection &rnc);
	void load(RecNameCollection &rnc);

	void clear();

	//UINT64List
	size_t nUINT64s();
	UINT64 getUINT64(size_t index);

protected:
	struct TrackID {
		int _kinectIndex;
		UINT64 _fromId;
		UINT64 _toId;
	};

	class TrackIDTable {
	public:
		TrackIDTable(TrackIDManager *tidm, int kinectIndex);
		~TrackIDTable();

		UINT64 getTrackID(UINT64 fromID);

	protected:
		TrackIDManager *_tidm;
		int _kinectIndex;
		map<UINT64, TrackID *> _trackIDs;
	};

	map<UINT64, TrackIDTable *> _trackIDTables;
	vector<TrackID *> _ids;
};

#endif
