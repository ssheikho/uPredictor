#include "QuadPack.h"

QuadPack::QuadPack() {}
QuadPack::~QuadPack() {}

GLUquadric *QuadPack::getQuad(size_t index) {
	while (index >= _quad.size())
		_quad.push_back(gluNewQuadric());
	return _quad[index];
}