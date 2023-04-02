#pragma once

#include "../Shared/DtxLibs.h"
#include "DtxApp.h"
#include "DtxCylinder.h"

class DtxObjectToWorld final
{
public:
    DtxObjectToWorld();
    ~DtxObjectToWorld() = default;

    DtxApp *GetApp();
private:
	DtxLibs mDtxLibs;
	DtxApp mDtxApp;
    DtxCylinder mDtxCylinder;
};
