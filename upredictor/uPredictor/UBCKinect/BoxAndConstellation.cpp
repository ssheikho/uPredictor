#include "BoxAndConstellation.h"

BoxAndConstellation::BoxAndConstellation(
	SimplePool<SubsetPt3DCollection>::PooledPtr pts) : _pts(pts)
{}
BoxAndConstellation::~BoxAndConstellation() {}

RegisteredBB &BoxAndConstellation::getBB() {
	return _bb;
}

SimplePool<SubsetPt3DCollection>::PooledPtr BoxAndConstellation::getPts() {
	return _pts;
}