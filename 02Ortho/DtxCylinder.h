#pragma once
#include "DtxMesh.h"

class DtxCylinder final
	: public DtxMesh
{
public:
	DtxCylinder(float radius = .5f, float height = 1.f, ULONG cnt = 12);
private:
	float mRadius;
	float mHeight;
	ULONG mSegmentCount;
};
