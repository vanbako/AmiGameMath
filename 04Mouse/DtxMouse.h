#pragma once

#include "../Shared/DtxLibs.h"
#include "DtxApp.h"
#include "DtxCylinder.h"

class DtxMouse final
{
public:
    DtxMouse();
    ~DtxMouse() = default;

    DtxApp *GetApp();
private:
	DtxLibs mDtxLibs;
	DtxApp mDtxApp;
    DtxCylinder mDtxCylinder;
};
