#ifndef SUBSET_PT_3D_COLLECTION_H
#define SUBSET_PT_3D_COLLECTION_H

#include "Pt3DCollection.h"

/*
#define PCL_NO_PRECOMPILE
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
*/

#include <cstdlib>
#include <vector>

class SubsetPt3DCollection : public Pt3DCollection {
public:
	SubsetPt3DCollection(
		int maxPts
		, Pt3DCollection *superset = NULL
	);
	~SubsetPt3DCollection();

	void setSuperset(Pt3DCollection *superset);
	void addIndex(int index);
	//void addIndices(std::vector<int> indices);
	void clear();

	void compile();

	//Pt3DCollection
	int getNPts();
	CameraSpacePoint *getCameraPt(int index);
	CameraSpacePoint *getCameraPts();
	ColorSpacePoint *getColorPt(int index);
	ColorSpacePoint *getColorPts();
	bool getColorIsGood(int index);
	bool *getColorIsGood();
	unsigned char *getBGR(int index);
	unsigned char *getBGR();

protected:
	void alloc();
	void realloc();
	int _maxPts, _nPts, *_indices;
	Pt3DCollection *_superset;

	CameraSpacePoint *_cameraSpacePoints;
	ColorSpacePoint *_colorSpacePoints;
	bool *_colorIsGood;
	unsigned char *_bgr;

};

#endif