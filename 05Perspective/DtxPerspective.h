#pragma once

#include "../Shared/DtxLibs.h"
#include "DtxApp.h"
#include "DtxCylinder.h"

class DtxPerspective final
{
public:
    DtxPerspective();
    ~DtxPerspective() = default;

    DtxApp *GetApp();
private:
	DtxLibs mDtxLibs;
	DtxApp mDtxApp;
    DtxCylinder mDtxCylinder;
};
