#ifndef GL_RENDER_INTERFACE_H
#define GL_RENDER_INTERFACE_H

class CameraViewportManager;

class GLRenderInterface {
public:
	virtual void initializeRenderer() = 0;
	virtual void render(CameraViewportManager *cvm) = 0;
};

#endif