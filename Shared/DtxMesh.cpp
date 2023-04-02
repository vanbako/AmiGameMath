#include "DtxMesh.h"
#include "DtxWindow.h"

DtxMesh::DtxMesh()
	: mVertices{}
	, mTriangles{}
{}

void DtxMesh::Render(DtxWindow* pDtxWindow)
{
	for (auto& triangle : mTriangles)
		RenderTriangle(
			pDtxWindow,
			mVertices[triangle[0]],
			mVertices[triangle[1]],
			mVertices[triangle[2]]
		);
}

void DtxMesh::RenderTriangle(DtxWindow *pDtxWindow, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3)
{
	float
		mX{ 640.f },
		mY{ 480.f },
		min{ -32767.f },
		max{ 32767.f };
	float
		x[]{ v1[0] + mX, v2[0] + mX, v3[0] + mX },
		y[]{ mY - v1[1], mY - v2[1], mY - v3[1] };
	if (x[0] < min || x[0] > max || y[0] < min || y[0] > max ||
		x[1] < min || x[1] > max || y[1] < min || y[1] > max ||
		x[2] < min || x[2] > max || y[2] < min || y[2] > max)
		return;
	std::vector<DtxPoint> dtxTriangle{
		{ WORD(x[0]), WORD(y[0]) },
		{ WORD(x[1]), WORD(y[1]) },
		{ WORD(x[2]), WORD(y[2]) }
	};
	pDtxWindow->DrawPolyLine(dtxTriangle);
}
