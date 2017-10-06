#ifndef KI_POINT_CLOUD_SOURCE_H
#define KI_POINT_CLOUD_SOURCE_H

#include "CameraModel.h"
#include "F4VectPt3DCol.h"
#include "KIBackProjector.h"
#include "KIDepthSource.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <point_cloud_src/point_cloud_src.h>

class KIPointCloudSource :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
    KIPointCloudSource(CameraModel &cm, KIDepthSource *depthSource);

    ~KIPointCloudSource() {
        //delete _backProjector;
        delete _vertMap;
        delete _normMap;
        cudaFree(_dFilteredDepth);
    }

	//KinectImageFrameRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

    const float *getDeviceDepth();

    void projectDepthMap();

	//FROM POINT_CLOUD_SOURCE_BASE
    // pass-through functions
    inline bool hasColor() const {
		return _depthSource->hasColor();
	}

    inline dart::ColorLayout getColorLayout() const {
		return _depthSource->getColorLayout();
	}

    inline bool hasTimestamps() const {
		return _depthSource->hasTimestamps();
	}

    inline uint64_t getDepthTime() const {
		return _depthSource->getDepthTime();
	}

    inline uint64_t getColorTime() const {
		return _depthSource->getColorTime();
	}

    inline void setFilteredNorms(bool filteredNorms) {
		_filteredNorms = filteredNorms;
	}

    inline void setFilteredVerts(bool filteredVerts) {
		_filteredVerts = filteredVerts;
	}

    inline void setSigmaDepth(float sigmaDepth) {
		_sigmaDepth = sigmaDepth;
	}

    inline void setSigmaPixels(float sigmaPixels) {
		_sigmaPixels = sigmaPixels;
	}

    // point cloud functions
    virtual float4 * getDeviceVertMap() {
		return _vertMap->devicePtr();
	}

    virtual float4 * getDeviceNormMap() {
		return _normMap->devicePtr();
	}

    virtual const float4 * getDeviceVertMap() const {
		return _vertMap->devicePtr();
	}

    virtual const float4 * getDeviceNormMap() const {
		return _normMap->devicePtr();
	}

    // TODO: get rid of this, used for injecting arbitrary point clouds
    inline void setVertMap(const float4 * vertMap) {
        memcpy(_vertMap->hostPtr(),vertMap,_vertMap->length()*sizeof(float4));
        _vertMap->syncHostToDevice();
        _vertsOnHost = true;
    }

    inline const float4 * getHostVertMap() {
        if (!_vertsOnHost) {
            _vertMap->syncDeviceToHost();
            _vertsOnHost = true;
        }
        return _vertMap->hostPtr();
    }

    inline const float4 * getHostNormMap() {
        if (!_normsOnHost) {
            _normMap->syncDeviceToHost();
            _normsOnHost = true;
        }
        return _normMap->hostPtr();
    }

    inline void cropBox(const float3 & min, const float3 & max) {
        dart::cropBox(_vertMap->devicePtr(),_cm._width,_cm._height,min,max);
        _vertsOnHost = false;
    }

    inline void maskPointCloud(const int * deviceMask) {
        dart::maskPointCloud(
			_vertMap->devicePtr(),_cm._width,_cm._height,deviceMask);
        _vertsOnHost = false;
    }

	CameraModel &getCM() {	return _cm;	}

protected:
	CameraModel &_cm;

    // -=-=-=-=- members -=-=-=-=-
    KIDepthSource *_depthSource;
    dart::KIBackProjector _backProjector;

    dart::MirroredVector<float4> * _vertMap;
    dart::MirroredVector<float4> * _normMap;

    bool _vertsOnHost, _normsOnHost;
    bool _filteredVerts, _filteredNorms;
    float _sigmaDepth, _sigmaPixels;

    float *_dFilteredDepth;
	int *_segs;

	const long _nPts;

public:
	F4VectPt3DCol _pts;
};

#endif
