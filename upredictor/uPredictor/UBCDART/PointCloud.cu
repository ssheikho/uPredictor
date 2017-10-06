__global__ void gpu_KIDepthToVertices(const float *depthIn,
                                    float4 * vertOut, int *segMap,
                                    const int width,
                                    const int height,
                                    const float2 pp,
                                    const float2 fl) {

    const int u = blockIdx.x*blockDim.x + threadIdx.x;
    const int v = blockIdx.y*blockDim.y + threadIdx.y;
    const int index = u + v*width;

    if (u >= width || v >= height)
        return;

    float depth = depthIn[index];// / 1000.0;
    vertOut[index] = make_float4( (u - pp.x)*(depth/fl.x),
                                  (v - pp.y)*(depth/fl.y),
                                  depth,
                                 //segMap[index] == 20 ? 1.0f : 0.0f);
                                 1.0f);

}

void KIDepthToVertices(const float *depthIn, float4 *vertOut, int *segMap
	, const int width, const int height, const float2 pp, const float2 fl) {
    dim3 block(16,8,1);
    dim3 grid( ceil( width / (float)block.x), ceil( height / (float)block.y ));

    gpu_KIDepthToVertices<<<grid,block>>>(depthIn, vertOut, segMap
		, width, height, pp, fl);
}
