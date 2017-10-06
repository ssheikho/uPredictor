#include "UBCDARTTrackerModelRenderer.h"
#include "UBCDARTTracker.h"

namespace dart {

UBCDARTTrackerModelRenderer::UBCDARTTrackerModelRenderer(
	UBCDARTTracker &tracker, int modelNo) :
	_tracker(tracker)
	, _modelNo(modelNo)
{}

UBCDARTTrackerModelRenderer::~UBCDARTTrackerModelRenderer() {}

//GLRenderInterface
void UBCDARTTrackerModelRenderer::initializeRenderer() {}

void UBCDARTTrackerModelRenderer::render(CameraViewportManager *cvm) {
    //_tracker.updatePose(_modelNo);
    _tracker.getModel(_modelNo).render();
    //_tracker.getModel(_modelNo).renderWireframe();
   	//_tracker.getModel(_modelNo).renderLabeled();
    //glEnable(GL_COLOR_MATERIAL);
   	//_tracker.getModel(_modelNo).renderVoxels(0.0f);
    //glDisable(GL_COLOR_MATERIAL);
}

}
