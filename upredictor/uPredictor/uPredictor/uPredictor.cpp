#include "SimplePool.h"

#include <iostream>

using namespace std;

class IntFactory : public TypeFactory<int> {
public:
	int *getInstance() {
		return new int();
	}
};

int main()
{
	IntFactory intF;
	SimplePool<int> sp(intF, 10);
	{
		SimplePool<int>::PooledPtr aP = sp.getInstance();
		cout << sp.poolSize() << endl;
		vector<SimplePool<int>::PooledPtr> v;
		v.push_back(aP);
		cout << sp.poolSize() << endl;
	}
	cout << sp.poolSize() << endl;

	getchar();

    return 0;
}

