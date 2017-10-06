#ifndef QUAD_PACK_H
#define QUAD_PACK_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

class QuadPack {
public:
	QuadPack();
	~QuadPack();

	GLUquadric *getQuad(size_t index);

protected:
	std::vector<GLUquadric *> _quad;
};

#endif
