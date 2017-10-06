#include "KinectCloudRender.h"
#include "KinectImageFrame.h"
#include "Point3DRGB.h"
#include "Pt3DCollection.h"
#include "Registration2D3D.h"

//#include <opencv2/opencv.hpp>
#include <GL/GL.h>

#include <cmath>
#include <iostream>

using namespace std;

//Pt3DCollection *pts
//_pts(pts)

KinectCloudRender::KinectCloudRender() : _kif(NULL) {}

KinectCloudRender::~KinectCloudRender() {}

void KinectCloudRender::processKinectImageFrame(KinectImageFrame *kif) {
	if (_kif) _kif->release();
	(_kif = kif)->claim();
}

void KinectCloudRender::render() {
	if (_kif) {
		Registration2D3D &reg = _kif->getR2D3D();

		int nPts = reg.getNPts();
		glBegin(GL_POINTS);
		for (int i = 0; i < nPts; i++) {
			Point3DRGB *pt = reg.getPt(i);
			if (pt->_colorIsGood) {
				glPointSize(5);
				//sets the current color
				glColor4ub(pt->_r, pt->_g, pt->_b, 100);

				glVertex3f(pt->_x3D, pt->_y3D, pt->_z3D);
			}
		}
		glEnd();
	}
}