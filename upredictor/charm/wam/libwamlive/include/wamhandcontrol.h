#ifndef WAM_HAND_CONTROL_H
#define WAM_HAND_CONTROL_H

#include "handcontrol.h"

#include <barrett/systems.h>
#include <barrett/systems/wam.h>
#include <barrett/units.h>
#include <barrett/products/hand.h>
#include <barrett/products/product_manager.h>

#include <barrett/math.h> 
#include <barrett/detail/stl_utils.h>

using namespace barrett;
using namespace std;

class WAMHandControl : public HandControl {
	public:
		WAMHandControl(Hand *hand);
		~WAMHandControl();

		void open(bool blocking = true);
		void close(bool blocking = true);

	protected:
		Hand *_hand;
};

#endif
