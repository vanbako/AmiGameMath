#pragma once

#include "../Shared/DtxLibs.h"
#include "DtxApp.h"
#include "DtxCylinder.h"

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
