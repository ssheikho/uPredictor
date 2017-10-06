#ifndef GL_KEY_HANDLER_H
#define GL_KEY_HANDLER_H

#include <GLFW/glfw3.h>

#include <map>
#include <vector>

using namespace std;

class GLKeyHandler {
public:
	static map<GLFWwindow*, vector<GLKeyHandler *> > _m;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	GLKeyHandler(GLFWwindow* window);
	~GLKeyHandler();

	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};

#endif