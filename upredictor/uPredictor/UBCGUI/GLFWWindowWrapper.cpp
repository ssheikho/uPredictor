#include "CameraViewportManager.h"
#include "GLFWWindowWrapper.h"
#include "RenderToggler.h"

//#include <cstdlib>
#include <cstdio>

GLFWWindowWrapper::GLFWWindowWrapper(string windowTitle) {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) exit(EXIT_FAILURE);
	_window = glfwCreateWindow(1280, 960, windowTitle.c_str(), NULL, NULL);
	
	if (!_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	_rt = new RenderToggler(_window);
	_cvm = new CameraViewportManager(_window);
	_cvm->rotateY(false, M_PI);
	_cvm->transZ(false, 2);

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);

	startup();
}

GLFWWindowWrapper::~GLFWWindowWrapper() {
	shutdown();
}

RenderToggler &GLFWWindowWrapper::getRenderToggler() {
	return *_rt;
}

void GLFWWindowWrapper::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void GLFWWindowWrapper::initializeRenderObjects() {
	if (isRunning()) {

		_cvm->projectionStep();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);

		_cvm->sceneStep();

		_rt->initializeRenderer();

		glfwSwapBuffers(_window);
		glfwPollEvents();

		if (glfwWindowShouldClose(_window)) shutdown();
	}
}

void GLFWWindowWrapper::render() {
	if (isRunning()) {

		_cvm->projectionStep();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);

		_cvm->sceneStep();

		_rt->render(_cvm);

		glfwSwapBuffers(_window);
		glfwPollEvents();

		if (glfwWindowShouldClose(_window)) shutdown();
	}
}

void GLFWWindowWrapper::onStartup() {}

void GLFWWindowWrapper::onShutdown() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void GLFWWindowWrapper::onAddChained(ShutdownInterface *si) {
	si = si;
}