#ifndef TRACKED_OBJECT_RENDERER_H
#define TRACKED_OBJECT_RENDERER_H

#include <WinSock2.h>
#include <Windows.h>

#include "Allocator.h"
#include "CloudRenderer.h"
#include "GLRenderInterface.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

class TrackedObjectRenderer :
	public GLRenderInterface
	, public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	TrackedObjectRenderer(
		UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc
		, int ptSize = 20);
	~TrackedObjectRenderer();

	//GLRenderInterface
	void render(CameraViewportManager *cvm);

	//TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr kf);
	void onStartup();

protected:
	SimplePool<KinectFrame>::PooledPtr _kf;
	int _ptSize;
	HANDLE _mutex;
};

#endif