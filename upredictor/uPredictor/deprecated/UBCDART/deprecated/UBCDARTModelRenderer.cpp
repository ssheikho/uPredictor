#include "UBCDARTModelRenderer.h"

#include <iostream>
#include "primitive_meshing.h"

namespace dart {
	UBCDARTModelRenderer::UBCDARTModelRenderer(UBCDARTMeshReader * meshReader) {
		// generate the primitive meshes
		Mesh * primitiveMeshes[NumPrimitives];
		primitiveMeshes[PrimitiveSphereType] = generateUnitIcosphereMesh(sphereSplits);
		primitiveMeshes[PrimitiveCylinderType] = generateCylinderMesh(cylinderSlices);
		primitiveMeshes[PrimitiveCubeType] = generateCubeMesh();

		// generate the buffers
		glGenBuffers(NumPrimitives, _primitiveVBOs);
		glGenBuffers(NumPrimitives, _primitiveNBOs);
		glGenBuffers(NumPrimitives, _primitiveIBOs);

		// copy data to buffers
		for (int i = 0; i<NumPrimitives; ++i) {
			Mesh * primitive = primitiveMeshes[i];

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _primitiveVBOs[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER
				, primitive->nVertices*sizeof(float3), primitive->vertices
				, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _primitiveNBOs[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, primitive->nVertices*sizeof(float3), primitive->normals, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _primitiveIBOs[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, primitive->nFaces*sizeof(int3), primitive->faces, GL_STATIC_DRAW);

			_nPrimitiveFaces[i] = primitive->nFaces;

			delete primitive;
		}

		// initialize mesh reader
		_meshReader = meshReader;
	}

	UBCDARTModelRenderer::~UBCDARTModelRenderer() {

		// free buffers
		glDeleteBuffers(NumPrimitives, _primitiveVBOs);
		glDeleteBuffers(NumPrimitives, _primitiveNBOs);
		glDeleteBuffers(NumPrimitives, _primitiveIBOs);

		if (_meshNumbers.size() > 0) {
			glDeleteBuffers(_meshNumbers.size(), _meshVBOs.data());
			glDeleteBuffers(_meshNumbers.size(), _meshNBOs.data());
			glDeleteBuffers(_meshNumbers.size(), _meshIBOs.data());
		}

		// free meshes
		for (int i = 0; i<_meshes.size(); ++i) {
			delete _meshes[i];
		}

		// free mesh reader
		delete _meshReader;
	}

	int UBCDARTModelRenderer::getMeshNumber(const std::string meshFilename) {

		if (_meshReader == 0) {
			std::cerr << "mesh reader was not set; therefore, meshes may not be read." << std::endl;
			return -1;
		}

		if (_meshNumbers.find(meshFilename) != _meshNumbers.end()) {
			return _meshNumbers[meshFilename];
		}

		Mesh * mesh = _meshReader->readMesh(meshFilename);

		if (mesh == 0) {
			std::cerr << "could not read " + meshFilename << std::endl;
			return -1;
		}

		int meshNum = _meshNumbers.size();
		_meshNumbers[meshFilename] = meshNum;

		_meshVBOs.resize(meshNum + 1);
		_meshNBOs.resize(meshNum + 1);
		_meshIBOs.resize(meshNum + 1);

		glGenBuffers(1, &_meshVBOs[meshNum]);
		glGenBuffers(1, &_meshNBOs[meshNum]);
		glGenBuffers(1, &_meshIBOs[meshNum]);

		glBindBuffer(GL_ARRAY_BUFFER, _meshVBOs[meshNum]);
		glBufferData(GL_ARRAY_BUFFER, mesh->nVertices*sizeof(float3), mesh->vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, _meshNBOs[meshNum]);
		glBufferData(GL_ARRAY_BUFFER, mesh->nVertices*sizeof(float3), mesh->normals, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _meshIBOs[meshNum]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nFaces*sizeof(int3), mesh->faces, GL_STATIC_DRAW);

		_nMeshFaces.push_back(mesh->nFaces);

		_meshes.push_back(mesh);

		return meshNum;

	}

	void UBCDARTModelRenderer::renderPrimitive(const GeomType type) const {

		glBindBuffer(GL_ARRAY_BUFFER, _primitiveNBOs[type]);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _primitiveVBOs[type]);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _primitiveIBOs[type]);

		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawElements(GL_TRIANGLES, 3 * _nPrimitiveFaces[type], GL_UNSIGNED_INT, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void UBCDARTModelRenderer::renderMesh(const unsigned int meshNum) const {

		glBindBuffer(GL_ARRAY_BUFFER, _meshNBOs[meshNum]);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _meshVBOs[meshNum]);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _meshIBOs[meshNum]);

		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawElements(GL_TRIANGLES, 3 * _nMeshFaces[meshNum], GL_UNSIGNED_INT, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	const Mesh & UBCDARTModelRenderer::getMesh(const unsigned int meshNum) const {

		return *_meshes[meshNum];

	}

	void UBCDARTModelRenderer::initializeRenderer() {
		
	}

	void UBCDARTModelRenderer::render(CameraViewportManager *cvm) {}

}
