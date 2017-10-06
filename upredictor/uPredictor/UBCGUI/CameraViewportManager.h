#ifndef CAMERA_VIEWPORT_MANAGER_H
#define CAMERA_VIEWPORT_MANAGER_H

#include "GLKeyHandler.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <GL/gl.h>

#include <cmath>

using namespace Eigen;

class CameraViewportManager {
public:
	CameraViewportManager(GLFWwindow* window);
	~CameraViewportManager();
	
	void projectionStep();
	void sceneStep(GLdouble *externalTrans = NULL);

	void rotateX(bool up, double rad = 2.0 * M_PI / 150.0);
	void rotateY(bool right, double rad = 2.0 * M_PI / 150.0);
	void rotateZ(bool right, double rad = 2.0 * M_PI / 150.0);
	void transX(bool right, double d = 0.05);
	void transY(bool up, double d = 0.05);
	void transZ(bool forward, double d = 0.05);

	//GLKeyHandler &getKeyHandler();

protected:
	class KeyHandler : public GLKeyHandler {
	public:
		KeyHandler(CameraViewportManager *cvm, GLFWwindow* window);
		~KeyHandler();

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	protected:
		CameraViewportManager *_cvm;
	};

	GLFWwindow* _window;
	double	_planeNear,			// Z near
		_planeFar,			// Z far
		_aspectRatio,		// aspect ratio
		_fov				// field of view in degree
		, _ratio
		;

	//Using pointers works around asserts that don't work well in Visual Studio
	Matrix4d _pose, _modelViewMatrix;

	KeyHandler _kh;
};

#endif
