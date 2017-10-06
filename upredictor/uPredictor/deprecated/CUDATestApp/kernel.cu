extern "C" {
	#include "CudaFunctions.h"
}

#include <stdio.h>

int main()
{
	return doCudaAdd();
}