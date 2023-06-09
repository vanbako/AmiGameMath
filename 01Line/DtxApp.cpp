#include "DtxApp.h"
#include <clib/exec_protos.h>

#include "../Shared/DtxWindow.h"

DtxApp::DtxApp()
    : mpDtxWindows{}
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
        signals = Wait(signalMask);
        for (DtxWindow *pDtxWindow : mpDtxWindows) {
            if (signals & pDtxWindow->GetSignalMask())
                while ((pIntuiMessage = (IntuiMessage *)GetMsg(pDtxWindow->GetWindow()->UserPort)) != NULL)
                {
                    switch (pIntuiMessage->Class)
                    {
                        case IDCMP_CLOSEWINDOW:
                            isDone = true;
                            break;
                    }
                    ReplyMsg((Message *)pIntuiMessage);
                }
        }
    }
}
