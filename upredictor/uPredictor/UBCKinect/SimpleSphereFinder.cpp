#include "SimpleSphereFinder.h"

#include <fstream>

using namespace std;

SimpleSphereFinder::SimpleSphereFinder(int gridSize) :
	_gridSize(gridSize)
	, _gridCells(_gridSize * _gridSize * _gridSize)
	, _bestCosts(new size_t[_gridCells])
	, _r(1.0)
	, _positions(new CameraSpacePoint[_gridCells])
	, _sphereCosts(new double[_gridCells]) {
	for (size_t i = 0; i < _gridCells; i++) _bestCosts[i] = i;
}

SimpleSphereFinder::~SimpleSphereFinder() {}

void SimpleSphereFinder::updateRadius(double r) { _r = r; }

void SimpleSphereFinder::processType(SimplePool<KinectFrame>::PooledPtr t) {
	t->_spheres.clear();

	map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>> &boxes =
		t->_boxes;
	for (
		map<int
		, vector < SimplePool<BoxAndConstellation>::PooledPtr >> ::iterator
		mIter = boxes.begin(); mIter != boxes.end(); mIter++) {
		vector < SimplePool<BoxAndConstellation>::PooledPtr > &v =
			mIter->second;
		for (vector <SimplePool<BoxAndConstellation>::PooledPtr>::iterator
			vIter = v.begin(); vIter != v.end(); vIter++) {
			searchForSpheres(*vIter);

			CameraSpacePoint p = _positions[_bestCosts[0]];

			UBCSphere s;
			s._x = p.X;
			s._y = p.Y;
			s._z = p.Z;
			s._r = _r;
			s._alpha = 1.0;

			t->_spheres[10].push_back(s);
		}
	}
}

void SimpleSphereFinder::onStartup() {}

void SimpleSphereFinder::searchForSpheres(
	SimplePool<BoxAndConstellation>::PooledPtr bac) {
	RegisteredBB &bb = bac->getBB();
	rescaleGrid(
		bb._minX3D, bb._maxX3D,
		bb._minY3D, bb._maxY3D,
		bb._minZ3D, bb._maxZ3D);

	for (int i = 0; i < 10; i++) {
		computeSphereCosts(bac);
		sortCosts();
		ThreeDBB bounds = findBestBounds(5);

		rescaleGrid(
			bounds._minX3D, bounds._maxX3D,
			bounds._minY3D, bounds._maxY3D,
			bounds._minZ3D, bounds._maxZ3D);
	}

	computeSphereCosts(bac);
	sortCosts();

	//Pick 3 best spheres
	//Find min,max x,y,z
	//rescaleGrid
	//Iterate
}

//Compute mean distance of all selected point cloud points to model sphere.
double SimpleSphereFinder::computeSphereCost(
	CameraSpacePoint *s, SimplePool<BoxAndConstellation>::PooledPtr bac) {
	double cost = 0.0;

	SimplePool<SubsetPt3DCollection>::PooledPtr pts = bac->getPts();
	int nPts = pts->getNPts();
	CameraSpacePoint *camPts = pts->getCameraPts();

	for (int i = 0; i < nPts; i++) {
		CameraSpacePoint &pt = camPts[i];
		cost += spheredist(s, pt.X, pt.Y, pt.Z, _r);
	}

	return cost;
}

//Compute cost for each sphere.
void SimpleSphereFinder::computeSphereCosts(SimplePool<BoxAndConstellation>::PooledPtr bac) {
	for (size_t i = 0; i < _gridCells; i++)
		_sphereCosts[i] = computeSphereCost(&_positions[i], bac);
}

ThreeDBB SimpleSphereFinder::findBestBounds(int nSpheres) {
	ThreeDBB retVal;

	CameraSpacePoint *curPos = &_positions[_bestCosts[0]];

	retVal._maxX3D = retVal._minX3D = curPos->X;
	retVal._maxY3D = retVal._minY3D = curPos->Y;
	retVal._maxZ3D = retVal._minZ3D = curPos->Z;

	for (int i = 1; i < nSpheres; i++) {
		curPos = &_positions[_bestCosts[i]];

		if (curPos->X < retVal._minX3D)	retVal._minX3D = curPos->X;
		if (curPos->Y < retVal._minY3D)	retVal._minY3D = curPos->Y;
		if (curPos->Z < retVal._minZ3D)	retVal._minZ3D = curPos->Z;

		if (curPos->X > retVal._maxX3D)	retVal._maxX3D = curPos->X;
		if (curPos->Y > retVal._maxY3D)	retVal._maxY3D = curPos->Y;
		if (curPos->Z > retVal._maxZ3D)	retVal._maxZ3D = curPos->Z;
	}

	return retVal;
}

//Compute width of grid + radius of sphere. Split into even slices.
void SimpleSphereFinder::rescaleGrid(
	double minX3D, double maxX3D,
	double minY3D, double maxY3D,
	double minZ3D, double maxZ3D) {
	double d = 2.0 * _r;
	double xMaxSpan = (maxX3D + d);
	double yMaxSpan = (maxY3D + d);
	double zMaxSpan = (maxZ3D + d);

	//Becomes a parameter in CUDA
	double xMinSpan = (minX3D - d);
	double yMinSpan = (minY3D - d);
	double zMinSpan = (minZ3D - d);

	double xSpan = xMaxSpan - xMinSpan;
	double ySpan = yMaxSpan - yMinSpan;
	double zSpan = zMaxSpan - zMinSpan;

	//Becomes a parameter in CUDA
	double xSliceWidth = xSpan / (double)(_gridSize);
	double ySliceWidth = ySpan / (double)(_gridSize);
	double zSliceWidth = zSpan / (double)(_gridSize);

	int ctr = 0;
	for (int i = 0; i < _gridSize; i++) {
		for (int j = 0; j < _gridSize; j++) {
			for (int k = 0; k < _gridSize; k++) {
				_positions[ctr].X = xMinSpan + _r + ((double)i * xSliceWidth);
				_positions[ctr].Y = yMinSpan + _r + ((double)j * ySliceWidth);
				_positions[ctr].Z = zMinSpan + _r + ((double)k * zSliceWidth);
				ctr++;
			}
		}
	}
}

void SimpleSphereFinder::sortCosts() {
	heapifyCosts();

	size_t endCell = _gridCells - 1;
	while (endCell > 0) {
		size_t pivot = _bestCosts[endCell];
		_bestCosts[endCell] = _bestCosts[0];
		_bestCosts[0] = pivot;
		endCell--;
		siftDownCosts(0, endCell);
	}

	saveCosts();
}

void SimpleSphereFinder::heapifyCosts() {
	//for (size_t i = 1; i < _gridCells; i++)
	//	siftUpCosts(0, i);
	int start = iParent(_gridCells - 1);
	while (start >= 0) {
		siftDownCosts(start, _gridCells - 1);
		start--;
	}
}

void SimpleSphereFinder::siftUpCosts(size_t start, size_t end) {
	size_t child = end;
	while (child > start) {
		size_t parent = floor((child - 1) / 2);
		if (_sphereCosts[_bestCosts[parent]] >
			_sphereCosts[_bestCosts[child]]) {
			size_t pivot = _bestCosts[child];
			_bestCosts[child] = _bestCosts[parent];
			_bestCosts[parent] = pivot;
			child = parent;
		}
		else {
			child = 0;
		}
	}
}

size_t SimpleSphereFinder::iParent(size_t child) {
	return floor((child - 1) / 2);
}

size_t SimpleSphereFinder::iLeftChild(size_t root) {
	return 2 * root + 1;
}

size_t SimpleSphereFinder::iRightChild(size_t root) {
	return 2 * root + 2;
}

void SimpleSphereFinder::siftDownCosts(size_t start, size_t end) {
	size_t root = start;
	while (iLeftChild(root) <= end) {
		size_t leftChild = iLeftChild(root);
		size_t rightChild = leftChild + 1;
		size_t swap = root;

		if (_sphereCosts[_bestCosts[swap]] < _sphereCosts[_bestCosts[leftChild]])
			swap = leftChild;

		if((rightChild <= end) && (_sphereCosts[_bestCosts[swap]] < _sphereCosts[_bestCosts[rightChild]]))
			swap = rightChild;

		if (swap == root) {
			return;
		}
		else {
			size_t pivot = _bestCosts[swap];
			_bestCosts[swap] = _bestCosts[root];
			_bestCosts[root] = pivot;
			root = swap;
		}
	}
}

void SimpleSphereFinder::saveCosts() {
	ofstream f("bestcosts.txt");
	for (size_t i = 0; i < _gridCells; i++) {
		f << _sphereCosts[_bestCosts[i]] << endl;
	}

	f << endl << endl;

	for (size_t i = 0; i < _gridCells; i++) {
		f << _bestCosts[i] << endl;
	}
	f.flush();
	f.close();
}