#ifndef SPHERE_GENERATOR_H
#define SPHERE_GENERATOR_H

#include "IntSwitch.h"
#include "Pt3DCollection.h"
#include "TypeBroadcaster.h"

#include <Eigen\core>
#include <memory>
#include <vector>

using namespace Eigen;
using namespace std;

class SphereDescription;

class SphereGenerator : 
	public TypeBroadcaster<Pt3DCollection *>
	, public IntSwitch
{
public:
	SphereGenerator(SphereDescription *sd);
	~SphereGenerator();

	void generateSphere();

	Pt3DCollection *getPts();

	//IntSwitch
	void updateSwitch(int val);

protected:
	void clear();
	void generateSpherePts();
	void generateSampleUnitVects();
	void scaleSampleVects();
	void generatePT3DCollection();

	SphereDescription *_sd;

	vector<MatrixXd> _sampleVectsU, _sampleVects, _samples;
	MatrixXd _c;

	Pt3DCollection *_pts;
};

#endif