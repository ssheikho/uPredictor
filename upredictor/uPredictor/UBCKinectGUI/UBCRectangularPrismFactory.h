#ifndef UBC_RECTANGULAR_PRISM_FACTORY_H
#define UBC_RECTANGULAR_PRISM_FACTORY_H

#include "TypeFactory.h"
#include "UBCRectangularPrism.h"

class UBCRectangularPrismFactory : public TypeFactory<UBCRectangularPrism> {
	UBCRectangularPrism *getInstance() {
		return new UBCRectangularPrism();
	}
};

#endif