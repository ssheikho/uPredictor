#include "Box3DRenderer.h"

Box3DRenderer::Box3DRenderer(int mode) :
	_mode(mode)
	, _colorGL(new GLfloat[4])
	, _prismCache(&_ubcpf)
	, _nBoxes(0)
//	, _quad(gluNewQuadric())
{
	setColor(0.0, 1.0, 1.0, 0.5);

	#ifdef _WIN32	
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif
}

Box3DRenderer::~Box3DRenderer() {
	delete[] _colorGL;
}

void Box3DRenderer::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	_colorGL[0] = r;
	_colorGL[1] = g;
	_colorGL[2] = b;
	_colorGL[3] = a;
}

void Box3DRenderer::initializeRenderer() {}

void Box3DRenderer::render(CameraViewportManager *cvm) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	for (size_t i = 0; i < _nBoxes; i++) _prismCache.get(i)->render(cvm);

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void Box3DRenderer::processType(SimplePool<KinectFrame>::PooledPtr t) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	switch (_mode) {
	case B3DR_MODE_BOXES:
	{
		map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>>
			boxes = t->_boxes;
		_nBoxes = 0;
		for (map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>>::iterator
			mIter = boxes.begin();
			mIter != boxes.end(); mIter++) {
			vector<SimplePool<BoxAndConstellation>::PooledPtr> &v = mIter->second;
			for (vector<SimplePool<BoxAndConstellation>::PooledPtr>::iterator
				vIter = v.begin();
				vIter != v.end(); vIter++) {
				UBCRectangularPrism *p = _prismCache.get(_nBoxes++);
				RegisteredBB &bb = (*vIter)->getBB();
				p->update(
					bb._minX3D, bb._maxX3D
					, bb._minY3D, bb._maxY3D
					, bb._minZ3D, bb._maxZ3D);
				p->setColor(_colorGL);
			}
		}
	}
	break;
	case B3DR_MODE_SPHERE_BB:
	{
		UBCRectangularPrism *p = _prismCache.get(0);
		p->update(
			t->_sdi._threeDBB._minX3D, t->_sdi._threeDBB._maxX3D
			, t->_sdi._threeDBB._minY3D, t->_sdi._threeDBB._maxY3D
			, t->_sdi._threeDBB._minZ3D, t->_sdi._threeDBB._maxZ3D);
		p->setColor(_colorGL);
		_nBoxes = 1;
	}
	}

	//_m = t->_spheres;

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void Box3DRenderer::onStartup() {}
