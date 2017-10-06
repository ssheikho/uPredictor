#include "UBCDARTPredictionRenderer.h"

#include <cuda_gl_interop.h>
#include "optimization/kernels/modToObs.h"
#include "optimization/kernels/raycast.h"
#include "util/cuda_utils.h"

#include <sys/time.h>

#include <GL/glx.h>

namespace dart {

const char * depthVertShaderSrc = "#version 130\n"
        "varying vec4 world_pos;\n"
        "uniform mat4 gl_ModelViewMatrix;"
        "void main(void)\n"
        "{\n"
        "       gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
        "       world_pos = gl_ModelViewMatrix*gl_Vertex;\n"
        "}\n";

const char * depthFragShaderSrc = "#version 130\n"
        "out vec4 out_Color;\n"
        "varying vec4 world_pos;\n"
        "void main(void)\n"
        "{\n"
        "   out_Color = vec4(world_pos.z,world_pos.z,world_pos.z,1.0);\n"
        "}\n";

const char * labeledVertShaderSrc = "#version 130\n"
        "varying vec4 world_pos;\n"
        "varying float id;\n"
        "uniform mat4 gl_ModelViewMatrix;"
        "void main()\n"
        "{\n"
        "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
        "   world_pos = gl_ModelViewMatrix*gl_Vertex;"
        "   id = gl_Color.x + gl_Color.z + 65536;\n"
        "}";

const char * labeledFragShaderSrc = "#version 130\n"
        "out vec4 out_Color;\n"
        "varying vec4 world_pos;\n"
        "varying float id;\n"
        "void main(void)\n"
        "{\n"
        "       out_Color = vec4(world_pos.x,world_pos.y,world_pos.z,id);\n"
        "}\n";

UBCDARTPredictionRenderer::UBCDARTPredictionRenderer(const int width, const int height, const float2 focalLength) :
     _focalLength(focalLength), _debugBoxIntersections(width*height) {

    _width = width;
    _height = height;

    cudaMalloc(&_dPrediction,width*height*sizeof(float4));
    cudaMemset(_dPrediction,0,width*height*sizeof(float4));
}

UBCDARTPredictionRenderer::~UBCDARTPredictionRenderer() {
    cudaFree(_dPrediction);

}


void UBCDARTPredictionRenderer::raytracePrediction(const MirroredModel & model, cudaStream_t & stream) {
    std::vector<const MirroredModel *> models(1);
    models[0] = &model;
    raytracePrediction(models,stream);
}

void UBCDARTPredictionRenderer::raytracePrediction(const std::vector<const MirroredModel *> & models, cudaStream_t & stream) {

    for (int m=0; m<models.size(); ++m) {
        raycastPrediction(_focalLength,
                          make_float2(_width/2,_height/2),
                          _width,_height,m,
                          models[m]->getTransformCameraToModel(),
                          models[m]->getDeviceTransformsModelToFrame(),
                          models[m]->getDeviceTransformsFrameToModel(),
                          models[m]->getDeviceSdfFrames(),
                          models[m]->getDeviceSdfs(),
                          models[m]->getNumSdfs(),
                          _dPrediction,0,
                          stream);
    }

    cudaStreamSynchronize(stream);

    _debugBoxIntersections.syncDeviceToHost();

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::cerr << "gpu_raytracePrediction error: %s\n" << cudaGetErrorString(err) << std::endl;
    }
}

void UBCDARTPredictionRenderer::cullUnobservable(const float4 * dObsVertMap,
                                          const int width,
                                          const int height,
                                          const cudaStream_t stream) {

    cullUnobservable_(_dPrediction,_width,_height,dObsVertMap,width,height,stream);

}

void UBCDARTPredictionRenderer::debugPredictionRay(const std::vector<const MirroredModel *> & models, const int x, const int y,
                                            std::vector<MirroredVector<float3> > & boxIntersects,
                                            std::vector<MirroredVector<float2> > & raySteps) {

    for (int m=0; m<models.size(); ++m) {
        std::cout << "debugging ray for " << m << std::endl;
        raycastPredictionDebugRay(_focalLength,
                                  make_float2(_width/2,_height/2),
                                  x,y,_width,m,
                                  models[m]->getTransformCameraToModel(),
                                  models[m]->getDeviceTransformsModelToFrame(),
                                  models[m]->getDeviceTransformsFrameToModel(),
                                  models[m]->getDeviceSdfFrames(),
                                  models[m]->getDeviceSdfs(),
                                  models[m]->getNumSdfs(),
                                  _dPrediction,0,
                                  boxIntersects[m].devicePtr(),
                                  raySteps[m].devicePtr(),raySteps[m].length());
        boxIntersects[m].syncDeviceToHost();
        raySteps[m].syncDeviceToHost();
    }
}

}
