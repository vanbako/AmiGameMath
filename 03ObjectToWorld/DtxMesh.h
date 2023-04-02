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
	float mScale;
	std::array<float, 3> mTranslation;
	std::array<float, 3> mRotation;
private:
	bool mHasMoved;
	std::vector<std::array<float, 4>> mTransformedVertices;
	std::array<float, 16> mObjectToWorldMatrix;

	static const std::array<float, 16> smIdentityMatrix;

	void RenderTriangle(DtxWindow* pDtxWindow, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
	std::array<float, 4> MatrixMultiply(const std::array<float, 16>& matrix, const std::array<float, 4>& vertex);
	std::array<float, 16> MatrixMultiply(const std::array<float, 16>& matrix1, const std::array<float, 16>& matrix2);
};
