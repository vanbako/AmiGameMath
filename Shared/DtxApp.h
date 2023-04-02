#pragma once

#include <vector>
#include <string>
#include "DtxRect.h"
#include "DtxSize.h"

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
};
