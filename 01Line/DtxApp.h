#pragma once

#include <vector>
#include <string>
#include "../Shared/DtxRect.h"
#include "../Shared/DtxSize.h"

class DtxWindow;

class DtxApp final
{
public:
    DtxApp();
    ~DtxApp();

    DtxWindow *AddWindow(const std::string& title, const DtxRect& dtxRect, const DtxSize& dtxMinSize, const DtxSize& dtxMaxSize);
    DtxWindow *AddWindow(const std::string& title, const DtxRect& dtxRect);
    DtxWindow *AddWindow(const std::string& title);
    void Loop();
private:
	std::vector<DtxWindow *> mpDtxWindows;
};
