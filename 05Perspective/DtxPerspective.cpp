#include "DtxPerspective.h"
#include "../Shared/DtxWindow.h"

DtxPerspective::DtxPerspective()
    : mDtxLibs{}
    , mDtxApp{}
    , mDtxCylinder{ 60.f, 180.f }
{
	DtxRect dtxRect{ 20, 20, 1280, 960 };
	DtxSize
		dtxMinSize{ 320, 240 },
		dtxMaxSize{ 1280, 960 };
	DtxWindow *pDtxWindow{ mDtxApp.AddWindow("GameMath, 05 Perpective", dtxRect, dtxMinSize, dtxMaxSize) };
	pDtxWindow->OpenWindow(true);
	mDtxApp.AddMesh(&mDtxCylinder);
}

DtxApp *DtxPerspective::GetApp()
{
    return &mDtxApp;
}
