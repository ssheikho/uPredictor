#ifndef INSTANCE_LOADER_H
#define INSTANCE_LOADER_H

#include "actorsorter.h"
#include "domainmap.h"

#include <string>

using namespace std;

class Problem;

class InstanceLoader {
	public:
		InstanceLoader(string domainFile, string problemFile, string actorFile);
		~InstanceLoader();

		DomainMap &getDomains();
		ActorSorter &getAS();

	protected:
		DomainMap _domains;
		ActorSorter _actorSorter;
};

#endif
