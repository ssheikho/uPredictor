#ifndef UBC_DART_MESH_READER_H
#define UBC_DART_MESH_READER_H

#include "mesh.h"
#include <string>

namespace dart {
	class UBCDARTMeshReader {
	public:
		virtual Mesh * readMesh(const std::string filename) const = 0;
	};
}

#endif