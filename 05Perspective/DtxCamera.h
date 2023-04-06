#pragma once

#include <exec/types.h>
#include <array>

class DtxCamera final
{
public:
	DtxCamera();
	std::array<float, 16>& GetView();
	std::array<float, 16>& GetViewInv();
	std::array<float, 16>& GetProj();
	void CalcViewProj();
	void SetAspectRatio(WORD width, WORD height);
private:
	std::array<float, 16>
		mView,
		mViewInv,
		mProj;
	std::array<float, 4>
		mPosition,
		mLookAt,
		mUp,
		mRight;
	float
		mFov,
		mAspectRatio,
		mNear,
		mFar;
	float Dot(const std::array<float, 4>& a, const std::array<float, 4>& b);
	std::array<float, 16> Inverse(const std::array<float, 16>& m);
	std::array<float, 16> MatrixMultiply(const std::array<float, 16>& matrix1, const std::array<float, 16>& matrix2);
};
