#include "kbresponse.h"
#include "paramlist.h"
#include "worldmodel.h"

#include <iostream>
#include <vector>

using namespace std;

KBResponse::KBResponse(WorldModel &wm) : _wm(wm) {}
KBResponse::~KBResponse() {}

void KBResponse::nextResponse() {
	vector<ParamList *> pl = _wm.computeApplicablePL();
	cout << "[0]:	Print State" << endl;
	for(int i = 0; i < pl.size(); i++) {
		cout << "[" << (i+1) << "]:	";
		pl[i]->printContents();
	}
	int response;
	cin >> response;
	if(response)
		_wm.apply(*pl[response - 1]);
	else
		_wm.getCurrentState()->printContents();
}

void *KBResponse::kbThread(void *in) {
	KBResponse *kb = (KBResponse *) in;
	while(true) {
		kb->nextResponse();
	}
}

void KBResponse::startThread() {
	pthread_create(&_thread, NULL, kbThread, this);
}

void KBResponse::waitThread() {
	pthread_join(_thread, NULL);
}
