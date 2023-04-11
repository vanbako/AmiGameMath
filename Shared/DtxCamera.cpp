#include "DtxCamera.h"
#include <cmath>

DtxCamera::DtxCamera(WORD width, WORD height)
	: mView{}
	, mViewInv{}
	, mProj{}
	, mPosition{ 0.f, 0.f, -500.f, 0.f }
	, mLookAt{ 0.f, 0.f, 1.f, 0.f }
	, mUp{ 0.f, 1.f, 0.f, 0.f }
	, mRight{ 1.f, 0.f, 0.f, 0.f }
	, mFov{ 3.14159265f / 3.f }
	, mAspectRatio{ static_cast<float>(width) / static_cast<float>(height) }
	, mNear{ 2.f }
	, mFar{ 5000.f }
{
	CalcViewProj();
}

std::array<float, 16>& DtxCamera::GetView()
{
    return mView;
}

std::array<float, 16>& DtxCamera::GetViewInv()
{
    return mViewInv;
}

std::array<float, 16>& DtxCamera::GetProj()
{
    return mProj;
}

void DtxCamera::CalcViewProj()
{
	mViewInv = std::array<float, 16>{
		mRight[0], mUp[0], mLookAt[0], -Dot(mRight, mPosition),
		mRight[1], mUp[1], mLookAt[1], -Dot(mUp, mPosition),
		mRight[2], mUp[2], mLookAt[2], -Dot(mLookAt, mPosition),
		0.f, 0.f, 0.f, 1.f
	};
	mView = Inverse(mViewInv);
    float fovTan{ std::tan(mFov / 2.f) };
	mProj = std::array<float, 16>{
		1.f / (mAspectRatio * fovTan), 0.f, 0.f, 0.f,
		0.f, 1.f / fovTan, 0.f, 0.f,
		0.f, 0.f, mFar / (mFar - mNear), 1.f,
		0.f, 0.f, -(mNear * mFar) / (mFar - mNear), 0.f
	};
}

void DtxCamera::SetAspectRatio(WORD width, WORD height)
{
    mAspectRatio = static_cast<float>(width) / static_cast<float>(height);
    CalcViewProj();
}

float DtxCamera::Dot(const std::array<float, 4>& a, const std::array<float, 4>& b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

std::array<float, 16> DtxCamera::Inverse(const std::array<float, 16>& m)
{
	std::array<float, 16> inv{};
	inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];
	
	float det{ m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12] };
	if (det == 0)
		return inv;
	det = 1.0f / det;
	for (int i{ 0 }; i < 16; i++)
		inv[i] = inv[i] * det;
	return inv;
}
