#include "poslist.h"
#include "printarmposer.h"
#include "printhandcontrol.h"
#include "printsafetycontrols.h"
#include "wamcontrolwindow.h"

int main(int argc, char **argv) {
	PosList pl(7);
	PrintArmPoser pap(7);
	PrintHandControl phc;
	PrintSafetyControls psc(1.5, 1.0);

	pl.load("../wamposer/joint_coordinates.txt");

	gtk_init(&argc, &argv);

	WAMControlWindow wcw(pl, pap, phc, psc);

	gtk_widget_show_all(wcw.getWindow());

	gtk_main();

	return 0;
}
