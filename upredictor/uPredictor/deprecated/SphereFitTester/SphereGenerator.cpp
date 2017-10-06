#include "SphereGenerator.h"
#include "ArrayPt3DCollection.h"
#include "Point3DRGB.h"
#include "SphereDescription.h"
#include "UBCUtil.h"

SphereGenerator::SphereGenerator(SphereDescription *sd) : _sd(sd), _c(3,1), _pts(NULL) {}

SphereGenerator::~SphereGenerator() {
	clear();
}

void SphereGenerator::clear() {
	_sampleVectsU.clear();
	_sampleVects.clear();
	_samples.clear();
	if (_pts) {
		delete _pts;
		_pts = NULL;
	}
}

void SphereGenerator::generateSphere() {
	generateSampleUnitVects();
	scaleSampleVects();
	generateSpherePts();
	generatePT3DCollection();
}

Pt3DCollection *SphereGenerator::getPts() {
	return _pts;
}

void SphereGenerator::generateSpherePts() {
	_c(0, 0) = _sd->_cX._t;
	_c(1, 0) = _sd->_cY._t;
	_c(2, 0) = _sd->_cZ._t;

	for (vector<MatrixXd>::iterator iter = _sampleVects.begin()
		; iter != _sampleVects.end(); iter++)
		_samples.push_back(*iter + _c);
}

void SphereGenerator::generateSampleUnitVects() {
	_sampleVectsU.clear();

	int nSamples = _sd->_nPts._t;
	for (int i = 0; i < nSamples; i++) {
		MatrixXd sphereRay(3, 1);
		sphereRay <<
			(rndDouble() * 2.0 - 1.0),
			(rndDouble() * 2.0 - 1.0),
			(rndDouble() * 2.0 - 1.0);
		sphereRay.normalize();

		_sampleVectsU.push_back(sphereRay);
	}
}

void SphereGenerator::scaleSampleVects() {
	_sampleVects.clear();

	double r = _sd->_rad._t;

	for (vector<MatrixXd>::iterator iter = _sampleVectsU.begin()
		; iter != _sampleVectsU.end(); iter++)
		_sampleVects.push_back(r * *iter);
}

void SphereGenerator::generatePT3DCollection() {
	int nSamples = _sd->_nPts._t;
	_pts = new ArrayPt3DCollection(nSamples);
	for (int i = 0; i < nSamples; i++) {
		Point3DRGB *p = _pts->getPt(i);
		//p->_x3D = _samples[i](0, 0);
		//p->_y3D = _samples[i](1, 0);
		//p->_z3D = _samples[i](2, 0);
		p->x = _samples[i](0, 0);
		p->y = _samples[i](1, 0);
		p->z = _samples[i](2, 0);
	}
	fireUpdate(_pts);
}

void SphereGenerator::updateSwitch(int val) {
	clear();
	generateSphere();
}