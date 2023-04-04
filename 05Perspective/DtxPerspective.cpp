#include "DtxPerspective.h"
#include "../Shared/DtxWindow.h"

DtxPerspective::DtxPerspective()
    : mDtxLibs{}
    , mDtxApp{}
    , mDtxCylinder{ 75.f, 200.f }
{
	DtxRect dtxRect{ 20, 20, 1280, 1024 };
	DtxSize
		dtxMinSize{ 320, 256 },
		dtxMaxSize{ 1280, 1024 };
	DtxWindow *pDtxWindow{ mDtxApp.AddWindow("GameMath, 05 Perpective", dtxRect, dtxMinSize, dtxMaxSize) };
	pDtxWindow->OpenWindow(true);
	mDtxApp.AddMesh(&mDtxCylinder);
	mDtxCylinder.Render(pDtxWindow);
}

DtxApp *DtxPerspective::GetApp()
{
    return &mDtxApp;
}
