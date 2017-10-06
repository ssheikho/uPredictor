#include "GLKeyHandler.h"

map<GLFWwindow*, vector<GLKeyHandler *> > GLKeyHandler::_m;

void GLKeyHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//cout << "key_callback" << endl;

	if (key == GLFW_KEY_ESCAPE && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
		glfwSetWindowShouldClose(window, GL_TRUE);

	vector<GLKeyHandler *> &v = _m[window];
	for (vector<GLKeyHandler *>::iterator i = v.begin(); i != v.end(); i++) {
		(*i)->keyCallback(window, key, scancode, action, mods);
	}

	//if (key == GLFW_KEY_S && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	//	renderBody = !renderBody;

	//if (key == GLFW_KEY_C && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	//	renderCloud = !renderCloud;
}

GLKeyHandler::GLKeyHandler(GLFWwindow* window) {
	_m[window].push_back(this);
	glfwSetKeyCallback(window, GLKeyHandler::key_callback);
}

GLKeyHandler::~GLKeyHandler() {}