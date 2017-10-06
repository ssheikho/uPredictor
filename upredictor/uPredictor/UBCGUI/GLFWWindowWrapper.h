#ifndef GLFW_WINDOW_WRAPPER_H
#define GLFW_WINDOW_WRAPPER_H

#include "DefaultShutdownInterface.h"

#include <GLFW/glfw3.h>

#include <string>

using namespace std;

class CameraViewportManager;
class RenderToggler;

class GLFWWindowWrapper : public DefaultShutdownInterface {
public:
	GLFWWindowWrapper(string windowTitle);
	~GLFWWindowWrapper();

	RenderToggler &getRenderToggler();

	void initializeRenderObjects();
	void render();

	static void error_callback(int error, const char* description);

protected:
	//ShutdownInterface
	void onStartup();
	void onShutdown();
	void onAddChained(ShutdownInterface *si);

	GLFWwindow *_window;
	RenderToggler *_rt;
	CameraViewportManager *_cvm;

};

#endif