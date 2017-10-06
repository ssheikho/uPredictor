#include "KinectSphereRenderer.h"
#include "CameraViewportManager.h"

// Temporary
#include <iostream>
using namespace std;

KinectSphereRenderer::KinectSphereRenderer(int mode, int maxSpheres) :
	_mode(mode)
	, _nsides(10)
	, _colorGL(new GLfloat[4])
	, _colorGLMat(new GLfloat[4 * maxSpheres])
	, _r(0.0) {
	setColor(0.0, 0.0, 1.0, 0.25);
	vector <UBCSphere> tmpList;
	_m.insert(pair<int, vector<UBCSphere>> (0, tmpList));
	
	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif
}

KinectSphereRenderer::~KinectSphereRenderer() {
	delete[] _colorGL;
	delete[] _colorGLMat;
}

void KinectSphereRenderer::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	_colorGL[0] = r;
	_colorGL[1] = g;
	_colorGL[2] = b;
	_colorGL[3] = a;
}

void KinectSphereRenderer::updateNSides(int nsides) {
	_nsides = nsides;
}

void KinectSphereRenderer::initializeRenderer() {}

void KinectSphereRenderer::render(CameraViewportManager *cvm) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	// cout << "RENDERING top" << endl;

	size_t index = 0;
	glPushMatrix();
	//cvm->sceneStep();

	// cout << "RENDERING " << endl;
	// cout << "WE ARE DOWN, size is " << _m[0].size() << endl;
	// cout << "WE ARE NOT DOWN, size is " << _m[0].size() << endl;

	for (int t = 0; t < _m[0].size(); t++) {
		// cout << "RENDERING DOWN" << endl;
		UBCSphere &s = _m[0][t];
		// cout << "Point: " << s._x << "," << s._y << "," << s._z << "," << s._r << endl;
		glPushMatrix();
		glColor4fv(_colorGL);
		//change origin to center
		glTranslatef(s._x, s._y, s._z);
		GLUquadric *quad = _qp.getQuad(index);		//gluNewQuadric();
		gluSphere(quad, s._r, _nsides, 10);
		index++;
		glPopMatrix();
	}

	// for (map<int, vector<UBCSphere>>::iterator mIter = _m.begin();
	// mIter != _m.end(); mIter++) {
	// 	cout << "RENDERING " << mIter->first << endl;
	// 	vector<UBCSphere> v = mIter->second;
	// 	cout << "WE ARE DOWN, size is " << v.size() << endl;
	// 	for (vector<UBCSphere>::iterator vIter = v.begin();
	// 	vIter != v.end(); vIter++) {
	// 		cout << "RENDERING DOWN" << endl;
	// 		UBCSphere &s = *vIter;
	// 		//cout << "Point: " << s._x << "," << s._y << "," << s._z << "," << s._r << endl;
	// 		glPushMatrix();
	// 		glColor4fv(_colorGL);
	// 		//change origin to center
	// 		glTranslatef(s._x, s._y, s._z);
	// 		GLUquadric *quad = _qp.getQuad(index);	//gluNewQuadric();
	// 		gluSphere(quad, s._r, _nsides, 10);
	// 		index++;
	// 		glPopMatrix();
	// 	}
	// }
	glPopMatrix();

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void KinectSphereRenderer::processType(SimplePool<KinectFrame>::PooledPtr t) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	switch (_mode) {
	case KSR_MODE_TRACKER_GRID: {
		cout << "I SHOULDN'T BE CALLED\n";
		_m.clear();
		GridParams &gp = t->_sdi.getGP();
		size_t nSpheres = gp._nGridCells;
		CameraSpacePoint *pts = t->_sdi.getCenters();
		for (size_t i = 0; i < nSpheres; i++) {
			UBCSphere s;
			s._r = gp._r;
			s._x = pts[i].X;
			s._y = pts[i].Y;
			s._z = pts[i].Z;
			_m[0].push_back(s);
		}
	}
		break;
	case KSR_MODE_SPHERES:
		_m = t->_spheres;
		break;
	}

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void KinectSphereRenderer::onStartup() {}

/*
	Could try adding sphere directly to KinectFrame, but it looks somewhat
	deprecated?
*/
void KinectSphereRenderer::addSphere(double x, double y, double z)
{
	UBCSphere s;
	s._r = 0.005;
	s._x = x;
	s._y = y;
	s._z = z;
	//cout << "Adding: (" << s._x << "," << s._y << "," << s._z << ")" << endl;
	_m[0].push_back(s);
	//cout << "THE SIZE IS " << _m[0].size() << endl;
}

void KinectSphereRenderer::clearSpheres()
{
	//cout <<"I WAS CALLED!\n";
	_m[0].clear();
}
