#pragma once

#include "../Shared/DtxLibs.h"
#include "../Shared/DtxApp.h"
#include "../Shared/DtxCylinder.h"

class DtxOrtho final
{
public:
    DtxOrtho();
    ~DtxOrtho() = default;

    DtxApp *GetApp();
private:
	DtxLibs mDtxLibs;
	DtxApp mDtxApp;
    DtxCylinder mDtxCylinder;
};
