#ifndef ALLOCATOR_H
#define ALLOCATOR_H

//Phase out TypeFactory for this.

namespace UBC {
	template<typename T> class Allocator {
	public:
		virtual T getInstance() = 0;
	};
}

#endif