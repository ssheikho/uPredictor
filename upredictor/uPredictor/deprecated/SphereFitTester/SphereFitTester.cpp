#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "CloudRenderer.h"
#include "ColumnLayout.h"
#include "GLFWWindowWrapper.h"
#include "GridLayout.h"
#include "RenderToggler.h"
#include "SimpleLabeledSlider.h"
#include "SphereDescription.h"
#include "SphereFitCostFunctor.h"
#include "SphereGenerator.h"
#include "ShutdownContainer.h"
#include "UBCButton.h"
#include "UBCEntry.h"
#include "UBCSphere.h"
#include "UBCUtil.h"

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "ceres/ceres.h"
#include "glog/logging.h"

#include <Eigen\core>

#include <mfapi.h>

#include <tchar.h>

#include <cmath>
#include <ctime>
#include <vector>

using namespace Eigen;
using namespace std;

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::DYNAMIC;
using ceres::Problem;
using ceres::Solver;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	srand(time(NULL));
	SphereDescription sd;
	SphereGenerator sg(&sd);
	sg.generateSphere();

	Problem problem;
	Solver::Options options;
	Solver::Summary summary;

	SphereFitCostFunctor *sfcf = new SphereFitCostFunctor(sg.getPts());
	CostFunction *cf = new 
		AutoDiffCostFunction<SphereFitCostFunctor, DYNAMIC, 1, 1, 1, 1>(
			sfcf, 1000);

	UBCSphere sphere;
	problem.AddResidualBlock(cf, NULL
		, &sphere._x._t, &sphere._y._t, &sphere._z._t, &sphere._r._t);

	ceres::Solve(options, &problem, &summary);

	/*
	SphereGeneratorOpenGL sgOpenGL(&sd);

	ShutdownContainer sc;

	AutoResizeWindow sphereControlW(hInstance, 100, 100);
	sc.addChainedSI(&sphereControlW);
	GridLayout gl(&sphereControlW, 100, 25);

	gl.addRow();
	UBCEntry xL(L"X", &gl, false, 100);
	SimpleLabeledSlider xSLS(&gl, 1000, 25, 0, 1000, 10, 1.0, false);

	gl.addRow();
	UBCEntry yL(L"Y", &gl, false, 100);
	SimpleLabeledSlider ySLS(&gl, 1000, 25, 0, 1000, 10, 1.0, false);

	gl.addRow();
	UBCEntry zL(L"Z", &gl, false, 100);
	SimpleLabeledSlider zSLS(&gl, 1000, 25, 0, 1000, 10, 1.0, false);

	xSLS.getSS().TypeBroadcaster<double>::addRecipient(&sd._cX);
	ySLS.getSS().TypeBroadcaster<double>::addRecipient(&sd._cY);
	zSLS.getSS().TypeBroadcaster<double>::addRecipient(&sd._cZ);

	gl.addRow();
	UBCButton generateB(L"Generate", &gl, &sg, 0, 100);

	GLFWWindowWrapper window("Pt Cloud");
	CloudRenderer cr(10000, 20);
	window.getRenderToggler().add(GLFW_KEY_C, &cr);
	window.getRenderToggler().add(GLFW_KEY_D, &sgOpenGL);
	sc.addChainedSI(&window);
	sg.addRecipient(&cr);

	while (sc.isRunning())	window.render();
	*/
    return 0;
}

