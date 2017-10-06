#include "SubsetPt3DCollection.h"

SubsetPt3DCollection::SubsetPt3DCollection(
	int maxPts
	, Pt3DCollection *superset) :
	_maxPts(maxPts)
	, _nPts(0)
	, _indices(new int[_maxPts])
	, _superset(superset)

	, _cameraSpacePoints(new CameraSpacePoint[_maxPts])
	, _colorSpacePoints(new ColorSpacePoint[_maxPts])
	, _colorIsGood(new bool[_maxPts])
	, _bgr(new unsigned char[_maxPts * 3])
{}

SubsetPt3DCollection::~SubsetPt3DCollection() {
	clear();
}

void SubsetPt3DCollection::setSuperset(Pt3DCollection *superset) {
	_superset = superset;
}

void SubsetPt3DCollection::addIndex(int index) {
	//_indices->indices.push_back(index);
	_indices[_nPts] = index;
	_nPts++;
}

void SubsetPt3DCollection::clear() {
	_nPts = 0;
	/*
	if (_cameraSpacePoints) {
		//delete[] _indices;
		delete[] _cameraSpacePoints;
		delete[] _colorSpacePoints;
		delete[] _colorIsGood;
		delete[] _bgr;

		//_indices = NULL;
		_cameraSpacePoints = NULL;
		_colorSpacePoints = NULL;
		_colorIsGood = NULL;
		_bgr = NULL;
	}
	*/
}

void SubsetPt3DCollection::alloc() {
	//_indices = new int[_nPts];
	_cameraSpacePoints = new CameraSpacePoint[_nPts];
	_colorSpacePoints = new ColorSpacePoint[_nPts];
	_colorIsGood = new bool[_nPts];
	_bgr = new unsigned char[_nPts * 3];
}

void SubsetPt3DCollection::realloc() {
	//_indices = new int[_nPts];
	delete[] _cameraSpacePoints;
	delete[] _colorSpacePoints;
	delete[] _colorIsGood;
	delete[] _bgr;

	_cameraSpacePoints = new CameraSpacePoint[_nPts];
	_colorSpacePoints = new ColorSpacePoint[_nPts];
	_colorIsGood = new bool[_nPts];
	_bgr = new unsigned char[_nPts * 3];
}

void SubsetPt3DCollection::compile() {
	//realloc();
	for (int i = 0; i < _nPts; i++) {
		CameraSpacePoint *cam =_superset->getCameraPt(_indices[i]);
		ColorSpacePoint *col = _superset->getColorPt(_indices[i]);
		uint8_t *bgr = _superset->getBGR(_indices[i]);

		_cameraSpacePoints[i].X = cam->X;
		_cameraSpacePoints[i].Y = cam->Y;
		_cameraSpacePoints[i].Z = cam->Z;

		_colorSpacePoints[i].X = col->X;
		_colorSpacePoints[i].Y = col->Y;

		int j = i * 3;
		_bgr[j] = bgr[0];
		_bgr[j + 1] = bgr[1];
		_bgr[j + 2] = bgr[2];

		_colorIsGood[i] = _superset->getColorIsGood(_indices[i]);
	}
}

//Pt3DCollection
int SubsetPt3DCollection::getNPts() {
	return _nPts;// _selectedPts.size();  _indices->indices.size();//
}

CameraSpacePoint *SubsetPt3DCollection::getCameraPt(int index) {
	return &_cameraSpacePoints[index];
}

CameraSpacePoint *SubsetPt3DCollection::getCameraPts() {
	return _cameraSpacePoints;
}

ColorSpacePoint *SubsetPt3DCollection::getColorPt(int index) {
	return &_colorSpacePoints[index];
}

ColorSpacePoint *SubsetPt3DCollection::getColorPts() {
	return _colorSpacePoints;
}

bool SubsetPt3DCollection::getColorIsGood(int index) {
	return _colorIsGood[index];
}

bool *SubsetPt3DCollection::getColorIsGood() {
	return _colorIsGood;
}

unsigned char *SubsetPt3DCollection::getBGR(int index) {
	return &_bgr[index];
}

unsigned char *SubsetPt3DCollection::getBGR() {
	return _bgr;
}