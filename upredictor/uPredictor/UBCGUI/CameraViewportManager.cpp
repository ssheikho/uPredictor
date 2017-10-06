#include "CameraViewportManager.h"
#include "UBCUtil.h"

#include <GL/glu.h>

CameraViewportManager::CameraViewportManager(GLFWwindow* window) :
	_window(window), _planeNear(0.1), _planeFar(10000.0), _aspectRatio(1.0)
	, _fov(40.0), _pose(Matrix4d::Identity()), _kh(this, window) {
	rotateZ(true, M_PI);
}

CameraViewportManager::~CameraViewportManager() {}

void CameraViewportManager::projectionStep() {
	glMatrixMode(GL_PROJECTION);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	//glLoadMatrixd(_poseGL);
	gluPerspective(_fov, _aspectRatio, _planeNear, _planeFar);

	//gluLookAt(	_posX,	_posY,	_posZ,			// eye is at (0,0,5)
	//			0.0,	0.0,	0.0,			// center is at (0,0,0)
	//			0.0,	1.0,	0.0);			// up is in positive Y direction
	//glTranslated(0.0, 0.0, -5.0);

	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	_ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void CameraViewportManager::sceneStep(GLdouble *externalTrans) {
	GLdouble modelViewMatrixGL[16];

	glMatrixMode(GL_MODELVIEW);
	copyEigenToGL(_pose, modelViewMatrixGL);
	glLoadMatrixd(modelViewMatrixGL);
	//glMultMatrixd(modelViewMatrixGL);

	//if(externalTrans) glMultMatrixd(externalTrans);

	glOrtho(-_ratio, _ratio, -1.0f, 1.0f, 1.0f, -1.0f);
}

void CameraViewportManager::rotateX(bool up, double rad) {
	_pose = rotX4(up ? rad : -rad) * _pose;
}

void CameraViewportManager::rotateY(bool right, double rad) {
	_pose = rotY4(right ? rad : -rad) * _pose;
}

void CameraViewportManager::rotateZ(bool right, double rad) {
	_pose = rotZ4(right ? rad : -rad) * _pose;
}

void CameraViewportManager::transX(bool right, double d) {
	_pose = transX4(right ? d : -d) * _pose;
}

void CameraViewportManager::transY(bool up, double d) {
	_pose = transY4(up ? -d : d) * _pose;
}

void CameraViewportManager::transZ(bool forward, double d) {
	_pose = transZ4(forward ? d : -d) * _pose;
}

CameraViewportManager::KeyHandler::KeyHandler(CameraViewportManager *cvm, GLFWwindow* window) : GLKeyHandler(window), _cvm(cvm) {}

CameraViewportManager::KeyHandler::~KeyHandler() {}

void CameraViewportManager::KeyHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ((action == GLFW_REPEAT) || (action == GLFW_PRESS)) {
		switch (mods) {
		case GLFW_MOD_SHIFT:
			switch (key) {
			case GLFW_KEY_W:
				cout << "W" << endl;
				_cvm->rotateX(true);
				break;
			case GLFW_KEY_S:
				cout << "S" << endl;
				_cvm->rotateX(false);
				break;
			case GLFW_KEY_A:
				cout << "A" << endl;
				_cvm->transX(false);
				break;
			case GLFW_KEY_D:
				cout << "D" << endl;
				_cvm->transX(true);
				break;
			default:
				break;
			}
			break;

		default:
			switch (key) {
			case GLFW_KEY_Q:
				_cvm->rotateZ(true);
				break;
			case GLFW_KEY_E:
				_cvm->rotateZ(false);
				break;
			case GLFW_KEY_W:
				cout << "W" << endl;
				_cvm->transZ(true);
				break;
			case GLFW_KEY_S:
				cout << "S" << endl;
				_cvm->transZ(false);
				break;
			case GLFW_KEY_A:
				cout << "A" << endl;
				_cvm->rotateY(false);
				break;
			case GLFW_KEY_D:
				cout << "D" << endl;
				_cvm->rotateY(true);
				break;
			case GLFW_KEY_R:
				_cvm->transY(true);
				break;
			case GLFW_KEY_F:
				_cvm->transY(false);
				break;
			default:
				break;
			}
			break;
		}
	}		
}
