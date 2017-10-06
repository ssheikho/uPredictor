#include "BoxRenderer.h"

BoxRenderer::BoxRenderer() :
	_bbColor(255, 255, 255) {}
BoxRenderer::~BoxRenderer() {}

void BoxRenderer::processType(SimplePool<KinectFrame>::PooledPtr t) {
	map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>> &boxes =
		t->_boxes;

	for (map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>>::iterator
		mIter = boxes.begin(); mIter != boxes.end(); mIter++) {
		vector<SimplePool<BoxAndConstellation>::PooledPtr> &vect =
			mIter->second;
		for (vector<SimplePool<BoxAndConstellation>::PooledPtr>::iterator
			vIter = vect.begin(); vIter != vect.end(); vIter++) {
			(*vIter)->getBB().drawBB(t->_sdi._depthSegImg, _bbColor, 1);
		}
	}
}