#include "RenderToggler.h"

RenderToggler::RenderToggler(GLFWwindow* window) : _kh(this, window) {}

RenderToggler::~RenderToggler() {}

void RenderToggler::add(int key, GLRenderInterface *r) {
	_ri[key] = r;
	_rend[key] = true;
}

void  RenderToggler::initializeRenderer() {
	for (map<int, GLRenderInterface *>::iterator i = _ri.begin(); i != _ri.end(); i++)
		if (_rend[i->first]) i->second->initializeRenderer();
}

void  RenderToggler::render(CameraViewportManager *cvm) {
	for (map<int, GLRenderInterface *>::iterator i = _ri.begin(); i != _ri.end(); i++)
		if (_rend[i->first]) i->second->render(cvm);
}

RenderToggler::KeyHandler::KeyHandler(RenderToggler *rt, GLFWwindow* window) : GLKeyHandler(window), _rt(rt) {}

RenderToggler::KeyHandler::~KeyHandler() {}

void RenderToggler::KeyHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		map<int, GLRenderInterface *>::iterator iter = _rt->_ri.find(key);
		if (iter != _rt->_ri.end()) _rt->_rend[key] = !_rt->_rend[key];
	}
}