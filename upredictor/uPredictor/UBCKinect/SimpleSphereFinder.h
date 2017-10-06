#ifndef SIMPLE_SPHERE_FINDER_H
#define SIMPLE_SPHERE_FINDER_H

#include "KinectFrame.h"
#include "SimplePool.h"
#include "ThreeDBB.h"
#include "TypeRecipient.h"
#include "UBCSimpleGeometry.h"

class SimpleSphereFinder :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	SimpleSphereFinder(int gridSize);
	~SimpleSphereFinder();

	void updateRadius(double r);

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	void searchForSpheres(SimplePool<BoxAndConstellation>::PooledPtr bac);
	double computeSphereCost(
		CameraSpacePoint *s, SimplePool<BoxAndConstellation>::PooledPtr bac);
	void computeSphereCosts(SimplePool<BoxAndConstellation>::PooledPtr bac);
	ThreeDBB findBestBounds(int nSpheres);
	void sortCosts();
	void saveCosts();
	void heapifyCosts();
	void siftUpCosts(size_t start, size_t end);
	void siftDownCosts(size_t start, size_t end);
	size_t iParent(size_t child);
	size_t iLeftChild(size_t root);
	size_t iRightChild(size_t root);

	//Generate a grid of candidate spheres
	void rescaleGrid(
		double minX3D, double maxX3D,
		double minY3D, double maxY3D,
		double minZ3D, double maxZ3D);

	int _gridSize, _gridCells;
	size_t *_bestCosts;
	double _r;
	CameraSpacePoint *_positions;
	double *_sphereCosts;
};

#endif