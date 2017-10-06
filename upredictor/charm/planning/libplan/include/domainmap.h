#ifndef DOMAIN_MAP_H
#define DOMAIN_MAP_H

#include <map>
#include <string>

using namespace std;

class Domain;

class DomainMap {
	public:
		DomainMap();
		~DomainMap();

		Domain *newDomain(string name);	
		Domain *getDomain(string name);	

	protected:
		void insertDomain(Domain *d, bool maintainPointer);

		map<string, Domain *> _m;
		map<string, bool> _maintainPointer;
};

#endif
