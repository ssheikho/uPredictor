#ifndef RENDER_TOGGLER_H
#define RENDER_TOGGLER_H

#include "GLKeyHandler.h"
#include "GLRenderInterface.h"

#include <GLFW/glfw3.h>

#include <map>

using namespace std;

class GLRenderInterface;

class RenderToggler : public GLRenderInterface {
public:
	RenderToggler(GLFWwindow* window);
	~RenderToggler();

	void add(int key, GLRenderInterface *r);

	void initializeRenderer();
	void render(CameraViewportManager *cvm);

protected:
	class KeyHandler : public GLKeyHandler {
	public:
		KeyHandler(RenderToggler *rt, GLFWwindow* window);
		~KeyHandler();

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	protected:
		RenderToggler *_rt;
	};

	map<int, GLRenderInterface *> _ri;
	map<int, bool> _rend;
	KeyHandler _kh;
};

#endif