#pragma once

#include <vector>
#include <string>
#include "../Shared/DtxRect.h"
#include "../Shared/DtxSize.h"
#include "../Shared/DtxPoint.h"
#include <intuition/intuition.h>

class DtxWindow;
class DtxMesh;

class DtxApp final
{
public:
    DtxApp();
    ~DtxApp();

    DtxWindow *AddWindow(const std::string& title, const DtxRect& dtxRect, const DtxSize& dtxMinSize, const DtxSize& dtxMaxSize);
    DtxWindow *AddWindow(const std::string& title, const DtxRect& dtxRect);
    DtxWindow *AddWindow(const std::string& title);
    void AddMesh(DtxMesh *pMesh);
    void Loop();
private:
	std::vector<DtxWindow *> mpDtxWindows;
    std::vector<DtxMesh *> mpMeshes;
    bool mMouseLeftDown;
    bool mMouseRightDown;
    DtxPoint mMousePos;
    ULONG mActiveMesh;

    void Render();
    void MouseMove(IntuiMessage *pIntuiMessage);
    void MouseButtons(IntuiMessage *pIntuiMessage);
};
