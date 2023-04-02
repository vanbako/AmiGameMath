#include "DtxOrtho.h"
#include "../Shared/DtxWindow.h"

DtxOrtho::DtxOrtho()
    : mDtxLibs{}
    , mDtxApp{}
    , mDtxCylinder{ 75.f, 200.f }
{
	DtxRect dtxRect{ 20, 20, 1280, 1024 };
	DtxSize
		dtxMinSize{ 320, 256 },
		dtxMaxSize{ 1280, 1024 };
	DtxWindow *pDtxWindow{ mDtxApp.AddWindow("GameMath, 01Line", dtxRect, dtxMinSize, dtxMaxSize) };
	pDtxWindow->OpenWindow();
	mDtxApp.AddMesh(&mDtxCylinder);
	mDtxCylinder.Render(pDtxWindow);
}

DtxApp *DtxOrtho::GetApp()
{
    return &mDtxApp;
}
