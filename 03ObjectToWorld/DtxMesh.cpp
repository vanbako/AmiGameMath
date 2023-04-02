#include "DtxMesh.h"
#include "../Shared/DtxWindow.h"
#include <cstring>
#include <cmath>

const std::array<float, 16> DtxMesh::smIdentityMatrix{
	1., 0., 0., 0.,
	0., 1., 0., 0.,
	0., 0., 1., 0.,
	0., 0., 0., 1.
};

DtxMesh::DtxMesh()
	: mVertices{}
	, mTriangles{}
	, mScale{ 1.f }
	, mTranslation{ 0.f, 0.f, 0.f }
	, mRotation{ 0.f, 0.f, 3.14159263f / 4.f }
	, mHasMoved{ true }
	, mTransformedVertices{}
	, mObjectToWorldMatrix{}
{}

void DtxMesh::Render(DtxWindow* pDtxWindow)
{
	if (mHasMoved)
	{
		mHasMoved = false;
		float c{}, s{};
		std::array<float, 16> r{};
		std::memcpy((void *)mObjectToWorldMatrix.data(), (void *)smIdentityMatrix.data(), 16 * sizeof(float));
		mObjectToWorldMatrix[0] = mScale;
		mObjectToWorldMatrix[5] = mScale;
		mObjectToWorldMatrix[10] = mScale;
		c = std::cos(mRotation[0]);
		s = std::sin(mRotation[0]);
		r = std::array<float, 16>{
			1., 0., 0., 0.,
			0., c, -s, 0.,
			0., s, c, 0.,
			0., 0., 0., 1. };
		mObjectToWorldMatrix = MatrixMultiply(r, mObjectToWorldMatrix);
		c = std::cos(mRotation[1]);
		s = std::sin(mRotation[1]);
		r = std::array<float, 16>{
			c, 0., s, 0.,
			0., 1., 0., 0.,
			-s, 0., c, 0.,
			0., 0., 0., 1. };
		mObjectToWorldMatrix = MatrixMultiply(r, mObjectToWorldMatrix);
		c = std::cos(mRotation[2]);
		s = std::sin(mRotation[2]);
		r = std::array<float, 16>{
			c, -s, 0., 0.,
			s, c, 0., 0.,
			0., 0., 1., 0.,
			0., 0., 0., 1. };
		mObjectToWorldMatrix = MatrixMultiply(r, mObjectToWorldMatrix);
		std::memcpy((void*)r.data(), (void*)smIdentityMatrix.data(), 16 * sizeof(float));
		r[3] = mTranslation[0];
		r[7] = mTranslation[1];
		r[11] = mTranslation[2];
		mObjectToWorldMatrix = MatrixMultiply(r, mObjectToWorldMatrix);
		mTransformedVertices.clear();
		mTransformedVertices.reserve(mVertices.size());
		for (auto& vertex : mVertices)
			mTransformedVertices.emplace_back(MatrixMultiply(mObjectToWorldMatrix, vertex));
	}
	for (auto& triangle : mTriangles)
		RenderTriangle(
			pDtxWindow,
			mTransformedVertices[triangle[0]],
			mTransformedVertices[triangle[1]],
			mTransformedVertices[triangle[2]]
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

std::array<float, 4> DtxMesh::MatrixMultiply(const std::array<float, 16>& matrix, const std::array<float, 4>& vertex)
{
	std::array<float, 4> result{};
	result[0] = matrix[0] * vertex[0] + matrix[1] * vertex[1] + matrix[2] * vertex[2] + matrix[3] * vertex[3];
	result[1] = matrix[4] * vertex[0] + matrix[5] * vertex[1] + matrix[6] * vertex[2] + matrix[7] * vertex[3];
	result[2] = matrix[8] * vertex[0] + matrix[9] * vertex[1] + matrix[10] * vertex[2] + matrix[11] * vertex[3];
	result[3] = matrix[12] * vertex[0] + matrix[13] * vertex[1] + matrix[14] * vertex[2] + matrix[15] * vertex[3];
	return result;
}

std::array<float, 16> DtxMesh::MatrixMultiply(const std::array<float, 16>& matrix1, const std::array<float, 16>& matrix2)
{
	std::array<float, 16> result{};
	for (ULONG row{ 0 }; row < 4; ++row)
		for (ULONG col{ 0 }; col < 4; ++col)
		{
			float sum{ 0 };
			for (ULONG i{ 0 }; i < 4; ++i)
				sum += matrix1[row * 4 + i] * matrix2[i * 4 + col];
			result[row * 4 + col] = sum;
		}
	return result;
}
