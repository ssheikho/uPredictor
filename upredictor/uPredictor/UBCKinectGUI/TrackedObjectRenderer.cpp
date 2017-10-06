#include "TrackedObjectRenderer.h"
#include "SubsetPt3DCollection.h"
#include "Point3DRGB.h"

#include <GL/GL.h>

TrackedObjectRenderer::TrackedObjectRenderer(
	UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc
	, int ptSize) :
	_kf(alloc.getInstance())
	, _ptSize(ptSize)
{
	_mutex = CreateMutex(NULL, FALSE, NULL);
}

TrackedObjectRenderer::~TrackedObjectRenderer() {}

void TrackedObjectRenderer::render(CameraViewportManager *cvm) {
	WaitForSingleObject(_mutex, INFINITE);
	map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>> &m =
		_kf->_boxes;
	for (
		map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>>::iterator
		mIter = m.begin(); mIter != m.end(); mIter++) {
		vector<SimplePool<BoxAndConstellation>::PooledPtr> &v = mIter->second;
		for (vector<SimplePool<BoxAndConstellation>::PooledPtr>::iterator
			vIter = v.begin(); vIter != v.end(); vIter++) {
			SimplePool<BoxAndConstellation>::PooledPtr bac = *vIter;
			glBegin(GL_POINTS);
			glPointSize(_ptSize);
			SimplePool<SubsetPt3DCollection>::PooledPtr ptCol = bac->getPts();
			CameraSpacePoint *pts = ptCol->getCameraPts();
			bool *colorIsGood = ptCol->getColorIsGood();
			int nPts = ptCol->getNPts();
			for (int i = 0; i < nPts; i++) {
				CameraSpacePoint &pt = pts[i];
				if (colorIsGood[i]) {
					//sets the current color
					//glColor4ub(pt->_r, pt->_g, pt->_b, 100);
					glColor4ub(255, 255, 255, 255);
					//glVertex3f(pt->_x3D, pt->_y3D, pt->_z3D);
					glVertex3f(pt.X, pt.Y, pt.Z);
				}
			}
			glEnd();
		}
	}

	ReleaseMutex(_mutex);
}

//TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
void TrackedObjectRenderer::processType(SimplePool<KinectFrame>::PooledPtr kf) {
	WaitForSingleObject(_mutex, INFINITE);
	_kf = kf;
	ReleaseMutex(_mutex);
}

void TrackedObjectRenderer::onStartup() {}