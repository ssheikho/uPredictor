#include "poslist.h"
#include "updatethread.h"
#include "wamarmposer.h"
#include "wamcontrolwindow.h"
#include "wamhandcontrol.h"
#include "wamsafetycontrols.h"

#include <barrett/systems.h>
#include <barrett/systems/wam.h>
#include <barrett/units.h>
#include <barrett/products/product_manager.h>

#include <barrett/math.h> 
#include <barrett/standard_main_function.h>
#include <barrett/detail/stl_utils.h>

using namespace barrett;
using namespace std;

template<size_t DOF> Hand *initHand(
	PosList &posList, ProductManager &pm, WAMArmPoser<DOF> &wam) {
	Hand *hand = NULL;

	if (pm.foundHand()) {
		cout << "Barrett Hand" << endl;
		hand = pm.getHand();
		
		wam.updatePose(posList.getPos("startup_position"));

		hand->initialize();
		hand->update();
		//usleep(150000);
		//hand->close(Hand::SPREAD);
		//hand->update();

	} else {
		cout << "Could not find Barrett Hand" << endl;
	}

	return hand;
}

template<size_t DOF>
int wam_main(int argc, char** argv, ProductManager& pm,
	systems::Wam<DOF>& wam) {	
	
	BARRETT_UNITS_TEMPLATE_TYPEDEFS(DOF);

	PosList pl(7);
	pl.load("joint_coordinates.txt");

	WAMArmPoser<DOF> pap(wam, "WAMArmPoser");

	Hand *hand = initHand<DOF>(pl, pm, pap);
	WAMHandControl phc(hand);

	WAMSafetyControls psc(pm.getSafetyModule());

	hand->close(Hand::SPREAD, false);

	wam.gravityCompensate();
	wam.idle();
	//hand->idle();

	gtk_init(&argc, &argv);

	WAMControlWindow wcw(pl, pap, phc, psc);
	gtk_widget_show_all(wcw.getWindow());

	UpdateThread ut(pap);
	ut.start();

	gtk_main();

	return 0;
}
