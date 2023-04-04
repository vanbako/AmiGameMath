#include "DtxCylinder.h"
#include <cmath>

DtxCylinder::DtxCylinder(float radius, float height, ULONG cnt)
	: DtxMesh()
	, mRadius{ radius }
	, mHeight{ height }
{
	DtxMesh::mVertices.reserve(cnt * 2 + 2);
	DtxMesh::mTriangles.reserve(cnt * 4);
	DtxMesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, 0.f, 0.f, 1.f});
	DtxMesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, mHeight, 0.f, 1.f});
	float
		x{}, z{},
		totalAngle{ 0.f },
		segmentAngle{ 2.f * 3.14159265f / float(cnt) };
	DtxMesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	DtxMesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	ULONG
		oldBottom{ 2 }, oldTop{ 3 },
		newBottom{ 4 }, newTop{ 5 };
	for (size_t i{ 1 }; i < cnt; ++i)
	{
		totalAngle += segmentAngle;
		x = std::cos(totalAngle) * mRadius;
		z = std::sin(totalAngle) * mRadius;
		DtxMesh::mVertices.emplace_back(std::array<float, 4>{ x, 0.f, z, 1.f });
		DtxMesh::mVertices.emplace_back(std::array<float, 4>{ x, mHeight, z, 1.f });
		DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ 0, oldBottom, newBottom });
		DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ 1, oldTop, newTop });
		DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ oldBottom, newBottom, oldTop });
		DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ oldTop, newBottom, newTop });
		oldBottom += 2;
		oldTop += 2;
		newBottom += 2;
		newTop += 2;
	}
	DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ 0, oldBottom, 2 });
	DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ 1, oldTop, 3 });
	DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ oldBottom, 2, oldTop });
	DtxMesh::mTriangles.emplace_back(std::array<ULONG, 3>{ oldTop, 2, 3 });
}
