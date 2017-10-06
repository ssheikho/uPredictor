#include "cuda_runtime.h"

extern "C" {
	int doCudaAdd();
}

cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);
__global__ void addKernel(int *c, const int *a, const int *b);
__global__ void generateRandomSphere(float *pts, float radius
	, float cx, float cy, float cz, unsigned long seed);