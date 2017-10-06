#include "ExternalUpdateCollection.h"

ExternalUpdateCollection::ExternalUpdateCollection() {}
ExternalUpdateCollection::~ExternalUpdateCollection() {}

void ExternalUpdateCollection::addEU(ExternalUpdate *eu) {
	_eu.push_back(eu);
}

void ExternalUpdateCollection::update() {
	for (vector<ExternalUpdate *>::iterator iter = _eu.begin();
	iter != _eu.end(); iter++) (*iter)->update();
}

bool ExternalUpdateCollection::hasFutureUpdates() {
	return true;
}

void ExternalUpdateCollection::onStartup() {
	for (vector<ExternalUpdate *>::iterator iter = _eu.begin(); iter != _eu.end(); iter++)
		(*iter)->onStartup();
}