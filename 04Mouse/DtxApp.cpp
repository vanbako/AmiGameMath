#include "DtxApp.h"
#include <clib/exec_protos.h>

#include "../Shared/DtxWindow.h"
#include "DtxMesh.h"

DtxApp::DtxApp()
    : mpDtxWindows{}
    , mpMeshes{}
    , mMouseLeftDown{ false }
    , mMouseRightDown{ false }
    , mMousePos{ 0, 0 }
    , mActiveMesh{ 0 }
{
}

DtxApp::~DtxApp()
{
    for (DtxWindow *pDtxWindow : mpDtxWindows)
        delete pDtxWindow;
}

DtxWindow *DtxApp::AddWindow(const std::string& title, const DtxRect& dtxRect, const DtxSize& dtxMinSize, const DtxSize& dtxMaxSize)
{
    DtxWindow *pDtxWindow = new DtxWindow{ title, dtxRect, dtxMinSize, dtxMaxSize };
    mpDtxWindows.emplace_back(pDtxWindow);
    return pDtxWindow;
}

DtxWindow *DtxApp::AddWindow(const std::string& title, const DtxRect& dtxRect)
{
    DtxSize
        dtxMinSize{ 320, 240 },
        dtxMaxSize{ 640, 480 };
    return AddWindow(title, dtxRect, dtxMinSize, dtxMaxSize);
}

DtxWindow *DtxApp::AddWindow(const std::string& title)
{
    DtxRect dtxRect{ 0, 0, 320, 240 };
    return AddWindow(title, dtxRect);
}

void DtxApp::AddMesh(DtxMesh *pMesh)
{
    mpMeshes.emplace_back(pMesh);
}

void DtxApp::Loop()
{
    ULONG
        signalMask{ 0 },
        signals{ 0 };
    for (DtxWindow *pDtxWindow : mpDtxWindows)
        signalMask |= pDtxWindow->GetSignalMask();
    bool isDone{ false };
    IntuiMessage *pIntuiMessage{ nullptr };
    while (!isDone)
    {
        Render();
        signals = Wait(signalMask);
        for (DtxWindow *pDtxWindow : mpDtxWindows)
            if (signals & pDtxWindow->GetSignalMask())
                while ((pIntuiMessage = (IntuiMessage *)GetMsg(pDtxWindow->GetWindow()->UserPort)) != NULL)
                {
                    switch (pIntuiMessage->Class)
                    {
                        case IDCMP_CLOSEWINDOW:
                            isDone = true;
                            break;
                        case IDCMP_MOUSEMOVE:
                            MouseMove(pIntuiMessage);
                            break;
                        case IDCMP_MOUSEBUTTONS:
                            MouseButtons(pIntuiMessage);
                            break;
                    }
                    ReplyMsg((Message *)pIntuiMessage);
                }
    }
}

void DtxApp::Render()
{
    if (mpDtxWindows.empty())
        return;
    DtxWindow *pDtxWindow{ mpDtxWindows[0] };
    pDtxWindow->Clear();
    for (DtxMesh *pMesh : mpMeshes)
        pMesh->Render(pDtxWindow);
    RefreshWindowFrame(pDtxWindow->GetWindow());
}

void DtxApp::MouseMove(IntuiMessage *pIntuiMessage)
{
    if (!(mMouseLeftDown || mMouseRightDown) || mpMeshes.empty())
        return;
    DtxPoint mouseDelta{ WORD(pIntuiMessage->MouseX - mMousePos.mX), WORD(pIntuiMessage->MouseY - mMousePos.mY) };
    mMousePos.mX = WORD(pIntuiMessage->MouseX);
    mMousePos.mY = WORD(pIntuiMessage->MouseY);
    mpMeshes[mActiveMesh]->MouseMove(mMouseLeftDown, mMouseRightDown, mouseDelta);
}

void DtxApp::MouseButtons(IntuiMessage *pIntuiMessage)
{
    switch (pIntuiMessage->Code)
    {
        case SELECTDOWN:
            mMouseLeftDown = true;
            mMousePos = { pIntuiMessage->MouseX, pIntuiMessage->MouseY };
    mpMeshes[mActiveMesh]->MouseMove(false, true, { 0, 10 });
            break;
        case MENUDOWN:
            mMouseRightDown = true;
            mMousePos = { pIntuiMessage->MouseX, pIntuiMessage->MouseY };
    mpMeshes[mActiveMesh]->MouseMove(false, true, { 10, 0 });
            break;
        case SELECTUP:
            mMouseLeftDown = false;
            break;
        case MENUUP:
            mMouseRightDown = false;
            break;
    }
}
