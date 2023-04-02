#pragma once

#include <exec/types.h>

#include <array>
#include <vector>

class DtxWindow;

class DtxMesh
{
public:
	DtxMesh();
	virtual ~DtxMesh() = default;

	virtual void Render(DtxWindow* pDtxWindow);
protected:
	std::vector<std::array<float, 4>> mVertices;
	std::vector<std::array<ULONG, 3>> mTriangles;
private:
	void RenderTriangle(DtxWindow* pDtxWindow, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
};
