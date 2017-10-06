#ifndef UBC_DART_MODEL_RENDERER_H
#define UBC_DART_MODEL_RENDERER_H

#include <map>
#include <string>
#include <vector>
#include <sys/types.h>
#include <GL/glew.h>

#include "mesh.h"
#include "dart_types.h"

#include "GLRenderInterface.h"
#include "UBCDARTMeshReader.h"

namespace dart {
	class UBCDARTModelRenderer :
	public GLRenderInterface {
	public:
		UBCDARTModelRenderer(UBCDARTMeshReader *meshReader = NULL);
		~UBCDARTModelRenderer();

		/**
		Returns the mesh number for a given mesh. If the mesh has not been seen before, a new mesh number is
		assigned and the mesh is loaded into memory.
		@param meshFilename The name of the file in which the mesh is stored.
		@return The unique mesh identifier if successful, otherwise -1.
		*/
		int getMeshNumber(const std::string meshFilename);

		void renderPrimitive(const GeomType type) const;

		/**
		Renders a mesh that is already loaded into memory.
		@param meshNum The unique identifier associated with the mesh.
		@see getMeshNumber()
		*/
		void renderMesh(const unsigned int meshNum) const;

		const Mesh & getMesh(const unsigned int meshNum) const;

		//GLRenderInterface
		void initializeRenderer();
		void render(CameraViewportManager *cvm);

	private:

		// primitive data
		GLuint _primitiveVBOs[NumPrimitives];
		GLuint _primitiveNBOs[NumPrimitives];
		GLuint _primitiveIBOs[NumPrimitives];
		int _nPrimitiveFaces[NumPrimitives];

		// mesh data
		std::map<std::string, unsigned int> _meshNumbers;
		std::vector<GLuint> _meshVBOs;
		std::vector<GLuint> _meshNBOs;
		std::vector<GLuint> _meshIBOs;
		std::vector<int> _nMeshFaces;
		std::vector<Mesh *> _meshes;

		// mesh loader
		UBCDARTMeshReader * _meshReader;

		static const int cylinderSlices = 20;
		static const int sphereSplits = 2;
	};

}

#endif // MODEL_RENDERER_H
