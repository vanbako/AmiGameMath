#include "DtxMouse.h"
#include "../Shared/DtxWindow.h"

DtxMouse::DtxMouse()
    : mDtxLibs{}
    , mDtxApp{}
    , mDtxCylinder{ 75.f, 200.f }
{
	DtxRect dtxRect{ 20, 20, 1280, 1024 };
	DtxSize
		dtxMinSize{ 320, 256 },
		dtxMaxSize{ 1280, 1024 };
	DtxWindow *pDtxWindow{ mDtxApp.AddWindow("GameMath, 04 Mouse", dtxRect, dtxMinSize, dtxMaxSize) };
	pDtxWindow->OpenWindow(true);
	mDtxApp.AddMesh(&mDtxCylinder);
}

DtxApp *DtxMouse::GetApp()
{
    return &mDtxApp;
}
