#ifndef UBC_DART_TRACKER_MODEL_RENDER_H
#define UBC_DART_TRACKER_MODEL_RENDER_H

#include "GLRenderInterface.h"

namespace dart {

class UBCDARTTracker;

class UBCDARTTrackerModelRenderer :
	public GLRenderInterface {
public:
	UBCDARTTrackerModelRenderer(UBCDARTTracker &tracker, int modelNo);
	~UBCDARTTrackerModelRenderer();

	//GLRenderInterface
	void initializeRenderer();
	void render(CameraViewportManager *cvm);

protected:
	UBCDARTTracker &_tracker;
	int _modelNo;
};

}

#endif
