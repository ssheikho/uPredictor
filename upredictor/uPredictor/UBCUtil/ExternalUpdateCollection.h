#ifndef EXTERNAL_UPDATE_COLLECTION_H
#define EXTERNAL_UPDATE_COLLECTION_H

#include "ExternalUpdate.h"

#include <vector>

using namespace std;

class ExternalUpdateCollection : public ExternalUpdate {
public:
	ExternalUpdateCollection();
	~ExternalUpdateCollection();

	void addEU(ExternalUpdate *eu);

	//ExternalUpdate
	void update();
	bool hasFutureUpdates();
	void onStartup();

protected:
	vector<ExternalUpdate *> _eu;
};

#endif